package io.github.dalamber.twopow;

import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

/** Loads the bundled {@code twopow_jni} native library. */
final class NativeLoader {

    private static boolean loaded = false;

    private NativeLoader() {}

    static synchronized void load() {
        if (loaded) {
            return;
        }
        try {
            System.loadLibrary("twopow_jni");
            loaded = true;
            return;
        } catch (UnsatisfiedLinkError ignored) {
            // Not on java.library.path; fall back to the bundled resource.
        }
        loaded = extractAndLoad();
    }

    private static boolean extractAndLoad() {
        final String libName = System.mapLibraryName("twopow_jni");
        final String resource = "/native/" + platformDir() + "/" + libName;
        try (InputStream in = NativeLoader.class.getResourceAsStream(resource)) {
            if (in == null) {
                throw new UnsatisfiedLinkError(
                    "twopow native library not bundled for this platform: "
                        + resource);
            }
            final int dot = libName.lastIndexOf('.');
            final String suffix = dot >= 0 ? libName.substring(dot) : ".lib";
            final Path tmp = Files.createTempFile("twopow_jni", suffix);
            tmp.toFile().deleteOnExit();
            Files.copy(in, tmp, StandardCopyOption.REPLACE_EXISTING);
            System.load(tmp.toAbsolutePath().toString());
            return true;
        } catch (IOException e) {
            throw new UnsatisfiedLinkError(
                "failed to load twopow native library: " + e.getMessage());
        }
    }

    private static String platformDir() {
        final String os = System.getProperty("os.name", "").toLowerCase();
        final String arch = System.getProperty("os.arch", "").toLowerCase();
        final String osDir =
            os.contains("mac") || os.contains("darwin") ? "darwin"
                : os.contains("win") ? "windows"
                : "linux";
        return osDir + "-" + arch;
    }
}
