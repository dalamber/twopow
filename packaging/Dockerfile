# syntax=docker/dockerfile:1
FROM debian:bookworm-slim AS build
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential cmake git ca-certificates && \
    rm -rf /var/lib/apt/lists/*
WORKDIR /src
COPY . .
RUN cmake -S . -B build \
        -DCMAKE_BUILD_TYPE=Release \
        -DTWOPOW_BUILD_TESTS=OFF \
        -DTWOPOW_BUILD_CLI=ON && \
    cmake --build build --target twopow-cli && \
    cmake --install build --prefix /opt/twopow

FROM debian:bookworm-slim AS runtime
LABEL org.opencontainers.image.source="https://github.com/OWNER/twopow"
LABEL org.opencontainers.image.description="Deterministic base-2 exponentiation"
LABEL org.opencontainers.image.licenses="Apache-2.0"
COPY --from=build /opt/twopow/bin/twopow-cli /usr/local/bin/twopow-cli
ENTRYPOINT ["twopow-cli"]
CMD ["2"]
