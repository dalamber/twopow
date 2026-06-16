// swift-tools-version:5.9
import PackageDescription

let package = Package(
    name: "Twopow",
    products: [
        .library(name: "Twopow", targets: ["Twopow"])
    ],
    targets: [
        .target(
            name: "CTwopow",
            path: "wrappers/swift/Sources/CTwopow",
            sources: ["twopow.cpp", "twopow_c.cpp"],
            publicHeadersPath: "include",
            cxxSettings: [.headerSearchPath("internal")]
        ),
        .target(
            name: "Twopow",
            dependencies: ["CTwopow"],
            path: "wrappers/swift/Sources/Twopow"
        ),
        .testTarget(
            name: "TwopowTests",
            dependencies: ["Twopow"],
            path: "wrappers/swift/Tests/TwopowTests"
        ),
    ],
    cxxLanguageStandard: .cxx20
)
