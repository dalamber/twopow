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
        -DTWOPOW_BUILD_CLI=OFF \
        -DTWOPOW_BUILD_SERVICE=ON && \
    cmake --build build --target twopow-service && \
    cmake --install build --prefix /opt/twopow

FROM debian:bookworm-slim AS runtime
LABEL org.opencontainers.image.source="https://github.com/dalamber/twopow"
LABEL org.opencontainers.image.description="twopow Exponentiation-as-a-Service"
LABEL org.opencontainers.image.licenses="Apache-2.0"
COPY --from=build /opt/twopow/bin/twopow-service /usr/local/bin/twopow-service
EXPOSE 8080
ENV PORT=8080
ENTRYPOINT ["twopow-service"]
