// twopow Exponentiation-as-a-Service — a production-grade HTTP surface for a
// single left shift.

#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

#include <httplib.h>

#include "twopow/twopow.hpp"

namespace {

constexpr int kDefaultPort = 8080;

std::string success_json(unsigned n, std::uint64_t result) {
    return "{\"base\":2,\"exponent\":" + std::to_string(n) +
           ",\"result\":\"" + std::to_string(result) +
           "\",\"result_uint64\":" + std::to_string(result) + "}";
}

std::string error_json(const std::string& code, const std::string& message) {
    return "{\"error\":{\"code\":\"" + code + "\",\"message\":\"" + message +
           "\"}}";
}

// Resolve an exponent string to a result, setting the HTTP response.
void handle_exponent(const std::string& raw, httplib::Response& res) {
    unsigned exponent = 0;
    try {
        std::size_t consumed = 0;
        const unsigned long parsed = std::stoul(raw, &consumed);
        if (consumed != raw.size() || parsed > 0xFFFFFFFFUL) {
            res.status = 400;
            res.set_content(error_json("invalid_exponent",
                                       "exponent must be a non-negative integer"),
                            "application/json");
            return;
        }
        exponent = static_cast<unsigned>(parsed);
    } catch (const std::exception&) {
        res.status = 400;
        res.set_content(
            error_json("invalid_exponent", "exponent could not be parsed"),
            "application/json");
        return;
    }

    try {
        const std::uint64_t result = twopow::two_pow(exponent);
        res.status = 200;
        res.set_content(success_json(exponent, result), "application/json");
    } catch (const twopow::overflow_error& e) {
        res.status = 422;
        res.set_content(error_json("overflow", e.what()), "application/json");
    }
}

const char* kOpenApi = R"YAML(openapi: 3.0.3
info:
  title: twopow Exponentiation-as-a-Service
  description: Deterministic base-2 exponentiation over HTTP.
  version: 0.1.0
  license:
    name: Apache-2.0
servers:
  - url: /
paths:
  /healthz:
    get:
      summary: Liveness probe
      responses:
        "200":
          description: Service is healthy
  /v1/pow/{n}:
    get:
      summary: Compute 2 raised to the power n
      parameters:
        - name: n
          in: path
          required: true
          schema: { type: integer, minimum: 0, maximum: 63 }
      responses:
        "200": { description: Successful computation }
        "400": { description: Invalid exponent }
        "422": { description: Exponent exceeds supported maximum }
  /v1/pow:
    get:
      summary: Compute 2 raised to the power n (query form)
      parameters:
        - name: n
          in: query
          required: true
          schema: { type: integer, minimum: 0, maximum: 63 }
      responses:
        "200": { description: Successful computation }
        "400": { description: Invalid exponent }
        "422": { description: Exponent exceeds supported maximum }
)YAML";

const char* kDocsHtml = R"HTML(<!doctype html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <title>twopow API — Swagger UI</title>
  <link rel="stylesheet" href="https://unpkg.com/swagger-ui-dist@5/swagger-ui.css">
</head>
<body>
  <div id="swagger-ui"></div>
  <script src="https://unpkg.com/swagger-ui-dist@5/swagger-ui-bundle.js"></script>
  <script>
    window.onload = () => {
      window.ui = SwaggerUIBundle({ url: '/openapi.yaml', dom_id: '#swagger-ui' });
    };
  </script>
</body>
</html>
)HTML";

}  // namespace

int main(int argc, char** argv) {
    int port = kDefaultPort;
    if (const char* env = std::getenv("PORT"); env != nullptr) {
        port = std::atoi(env);
    }
    if (argc > 1) {
        port = std::atoi(argv[1]);
    }

    httplib::Server svr;

    svr.Get("/healthz", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("{\"status\":\"ok\"}", "application/json");
    });

    svr.Get("/openapi.yaml", [](const httplib::Request&, httplib::Response& res) {
        res.set_content(kOpenApi, "application/yaml");
    });

    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_content(kDocsHtml, "text/html");
    });

    svr.Get(R"(/v1/pow/(\d+))",
            [](const httplib::Request& req, httplib::Response& res) {
                handle_exponent(req.matches[1].str(), res);
            });

    svr.Get("/v1/pow", [](const httplib::Request& req, httplib::Response& res) {
        if (!req.has_param("n")) {
            res.status = 400;
            res.set_content(error_json("missing_parameter",
                                       "query parameter 'n' is required"),
                            "application/json");
            return;
        }
        handle_exponent(req.get_param_value("n"), res);
    });

    std::cout << "twopow service listening on :" << port << "\n";
    if (!svr.listen("0.0.0.0", port)) {
        std::cerr << "twopow service: failed to bind port " << port << "\n";
        return 1;
    }
    return 0;
}
