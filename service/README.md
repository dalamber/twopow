# twopow Exponentiation-as-a-Service

A production-grade HTTP surface for `two_pow`. Because every capability deserves
an API.

## Run

```bash
cmake -S . -B build -DTWOPOW_BUILD_SERVICE=ON
cmake --build build --target twopow-service
./build/service/twopow-service 8080      # or set PORT=8080
```

Or via container:

```bash
docker build -f service/Dockerfile -t twopow-service .
docker run --rm -p 8080:8080 twopow-service
```

## Endpoints

| Method & path        | Description                              |
|----------------------|------------------------------------------|
| `GET /healthz`       | Liveness probe.                          |
| `GET /v1/pow/{n}`    | Compute `2^n` (path form).               |
| `GET /v1/pow?n={n}`  | Compute `2^n` (query form).              |
| `GET /openapi.yaml`  | The OpenAPI 3.0 specification.           |
| `GET /`              | Swagger UI.                              |

### Example

```bash
$ curl -s localhost:8080/v1/pow/10
{"base":2,"exponent":10,"result":"1024","result_uint64":1024}

$ curl -s -o /dev/null -w '%{http_code}\n' localhost:8080/v1/pow/64
422
```

Results are returned both as a decimal string (`result`, always exact) and as a
JSON number (`result_uint64`). Exponents above 63 return `422`; unparseable
exponents return `400`.

## Notes

Built on [cpp-httplib](https://github.com/yhirose/cpp-httplib) (fetched at build
time). The Swagger UI page loads assets from a public CDN at runtime; the API
itself has no network dependencies.
