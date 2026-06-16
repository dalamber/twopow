package io.github.dalamber.twopow

import java.nio.file.Files
import java.nio.file.StandardCopyOption

/** Loads the bundled `twopow_jni` native library. */
internal object NativeLoader {

    @Volatile
    private var loaded = false

    @Synchronized
    fun load() {
        if (loaded) return
        try {
            System.loadLibrary("twopow_jni")
            loaded = true
            return
        } catch (_: UnsatisfiedLinkError) {
            // Not on java.library.path; fall back to the bundled resource.
        }

        val libName = System.mapLibraryName("twopow_jni")
        val resource = "/native/${platformDir()}/$libName"
        val stream = NativeLoader::class.java.getResourceAsStream(resource)
            ?: throw UnsatisfiedLinkError(
                "twopow native library not bundled for this platform: $resource"
            )
        val suffix = libName.substringAfterLast('.', "lib")
        val tmp = Files.createTempFile("twopow_jni", ".$suffix")
        tmp.toFile().deleteOnExit()
        stream.use { Files.copy(it, tmp, StandardCopyOption.REPLACE_EXISTING) }
        System.load(tmp.toAbsolutePath().toString())
        loaded = true
    }

    private fun platformDir(): String {
        val os = System.getProperty("os.name", "").lowercase()
        val arch = System.getProperty("os.arch", "").lowercase()
        val osDir = when {
            os.contains("mac") || os.contains("darwin") -> "darwin"
            os.contains("win") -> "windows"
            else -> "linux"
        }
        return "$osDir-$arch"
    }
}
