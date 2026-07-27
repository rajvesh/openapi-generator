# cpp-httplib-server - C++ Server

## Overview

This server was generated using the [OpenAPI Generator](https://openapi-generator.tech) project.
It uses the [cpp-httplib](https://github.com/yhirose/cpp-httplib) library to implement a lightweight HTTP server
with JSON request/response handling via [nlohmann/json](https://github.com/nlohmann/json).

## Requirements

- C++17 compatible compiler
- CMake (3.14 or higher)
- OpenSSL (for HTTPS support)
- ZLIB (for compression support)

**Note:** The following libraries are automatically downloaded via CMake FetchContent:
- [cpp-httplib](https://github.com/yhirose/cpp-httplib) v0.15.3
- [nlohmann/json](https://github.com/nlohmann/json) v3.11.3

### Platform-Specific Installation

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get update
sudo apt-get install -y libssl-dev zlib1g-dev cmake build-essential
```

**macOS:**
```bash
brew install openssl zlib cmake
```

**Windows:**
```powershell
# Using vcpkg
vcpkg install openssl:x64-windows zlib:x64-windows

# Then configure CMake with vcpkg toolchain:
cmake -B build -DCMAKE_TOOLCHAIN_FILE=[vcpkg_root]/scripts/buildsystems/vcpkg.cmake
```

## Project Structure

```
├── CMakeLists.txt          # Project build configuration
├── README.md               # This file
├── models/                  # Generated model classes
└── api/                    # Generated API handler classes
```

## Building the Project

```bash
mkdir build
cd build
cmake ..
make
```

## Working with Models

### Model Classes

#### models::ApiResponse

```cpp
// Create a model
auto model = models::ApiResponse();
model.setCode(/* value */);  // Set code
model.setType(/* value */);  // Set type
model.setMessage(/* value */);  // Set message

// Serialize to JSON
nlohmann::json json = models::ApiResponse::toJson(model);
std::string jsonString = json.dump();

// Deserialize from JSON
auto parsedModel = models::ApiResponse::fromJson(nlohmann::json::parse(jsonString));
```
#### models::Category

```cpp
// Create a model
auto model = models::Category();
model.setId(/* value */);  // Set id
model.setName(/* value */);  // Set name

// Serialize to JSON
nlohmann::json json = models::Category::toJson(model);
std::string jsonString = json.dump();

// Deserialize from JSON
auto parsedModel = models::Category::fromJson(nlohmann::json::parse(jsonString));
```
#### models::Order

```cpp
// Create a model
auto model = models::Order();
model.setId(/* value */);  // Set id
model.setPetId(/* value */);  // Set petId
model.setQuantity(/* value */);  // Set quantity
model.setShipDate(/* value */);  // Set shipDate
model.setStatus(/* value */);  // Set status
model.setComplete(/* value */);  // Set complete

// Serialize to JSON
nlohmann::json json = models::Order::toJson(model);
std::string jsonString = json.dump();

// Deserialize from JSON
auto parsedModel = models::Order::fromJson(nlohmann::json::parse(jsonString));
```
#### models::Pet

```cpp
// Create a model
auto model = models::Pet();
model.setId(/* value */);  // Set id
model.setCategory(/* value */);  // Set category
model.setName(/* value */);  // Set name
model.setPhotoUrls(/* value */);  // Set photoUrls
model.setTags(/* value */);  // Set tags
model.setStatus(/* value */);  // Set status

// Serialize to JSON
nlohmann::json json = models::Pet::toJson(model);
std::string jsonString = json.dump();

// Deserialize from JSON
auto parsedModel = models::Pet::fromJson(nlohmann::json::parse(jsonString));
```
#### models::Tag

```cpp
// Create a model
auto model = models::Tag();
model.setId(/* value */);  // Set id
model.setName(/* value */);  // Set name

// Serialize to JSON
nlohmann::json json = models::Tag::toJson(model);
std::string jsonString = json.dump();

// Deserialize from JSON
auto parsedModel = models::Tag::fromJson(nlohmann::json::parse(jsonString));
```
#### models::User

```cpp
// Create a model
auto model = models::User();
model.setId(/* value */);  // Set id
model.setUsername(/* value */);  // Set username
model.setFirstName(/* value */);  // Set firstName
model.setLastName(/* value */);  // Set lastName
model.setEmail(/* value */);  // Set email
model.setPassword(/* value */);  // Set password
model.setPhone(/* value */);  // Set phone
model.setUserStatus(/* value */);  // Set userStatus

// Serialize to JSON
nlohmann::json json = models::User::toJson(model);
std::string jsonString = json.dump();

// Deserialize from JSON
auto parsedModel = models::User::fromJson(nlohmann::json::parse(jsonString));
```

## Implementing API Handlers

### API Classes

Each API is generated as an abstract base class with pure virtual methods that you must implement.

#### Pet

Create a class that inherits from the generated base class:

```cpp
#include "api/PetApi.h"

class PetImpl : public Api::Pet {
public:
    PetPostResponse handlePostForPet(const PetPostRequest& params) override {
        // Access request parameters:
        // Body: params.m_request (std::optional<models::Pet>)

        // Implement your business logic here

        // Return success response (HTTP HTTP_RESPONSE_CODE_PET):
        models::Pet successResponse;
        // ... populate response ...
        return successResponse;
    }

    void handleDeleteForPetpetId(const PetpetIdDeleteRequest& params) override {
        // Access request parameters from params struct
        // Implement your logic here
    }

    PetfindByStatusGetResponse handleGetForPetfindByStatus(const PetfindByStatusGetRequest& params) override {
        // Access request parameters:
        // Query: params.m_status

        // Implement your business logic here

        // Return success response (HTTP HTTP_RESPONSE_CODE_PET):
        models::Pet successResponse;
        // ... populate response ...
        return successResponse;
    }

    PetfindByTagsGetResponse handleGetForPetfindByTags(const PetfindByTagsGetRequest& params) override {
        // Access request parameters:
        // Query: params.m_tags

        // Implement your business logic here

        // Return success response (HTTP HTTP_RESPONSE_CODE_PET):
        models::Pet successResponse;
        // ... populate response ...
        return successResponse;
    }

    PetpetIdGetResponse handleGetForPetpetId(const PetpetIdGetRequest& params) override {
        // Access request parameters:
        // Path: params.m_petId

        // Implement your business logic here

        // Return success response (HTTP HTTP_RESPONSE_CODE_PET):
        models::Pet successResponse;
        // ... populate response ...
        return successResponse;
    }

    PetPutResponse handlePutForPet(const PetPutRequest& params) override {
        // Access request parameters:
        // Body: params.m_request (std::optional<models::Pet>)

        // Implement your business logic here

        // Return success response (HTTP HTTP_RESPONSE_CODE_PET):
        models::Pet successResponse;
        // ... populate response ...
        return successResponse;
    }

    void handlePostForPetpetId(const PetpetIdPostRequest& params) override {
        // Access request parameters from params struct
        // Implement your logic here
    }

    PetpetIduploadImagePostResponse handlePostForPetpetIduploadImage(const PetpetIduploadImagePostRequest& params) override {
        // Access request parameters:
        // Path: params.m_petId

        // Implement your business logic here

        // Return success response (HTTP HTTP_RESPONSE_CODE_API_RESPONSE):
        models::ApiResponse successResponse;
        // ... populate response ...
        return successResponse;
    }

};
```
#### Store

Create a class that inherits from the generated base class:

```cpp
#include "api/StoreApi.h"

class StoreImpl : public Api::Store {
public:
    void handleDeleteForStoreorderorderId(const StoreorderorderIdDeleteRequest& params) override {
        // Access request parameters from params struct
        // Implement your logic here
    }

    StoreinventoryGetResponse handleGetForStoreinventory() override {

        // Implement your business logic here

        // Return success response (HTTP HTTP_RESPONSE_CODE_PRIMITIVE_INTEGER):
        int successResponse;
        // ... populate response ...
        return successResponse;
    }

    StoreorderorderIdGetResponse handleGetForStoreorderorderId(const StoreorderorderIdGetRequest& params) override {
        // Access request parameters:
        // Path: params.m_orderId

        // Implement your business logic here

        // Return success response (HTTP HTTP_RESPONSE_CODE_ORDER):
        models::Order successResponse;
        // ... populate response ...
        return successResponse;
    }

    StoreorderPostResponse handlePostForStoreorder(const StoreorderPostRequest& params) override {
        // Access request parameters:
        // Body: params.m_request (std::optional<models::Order>)

        // Implement your business logic here

        // Return success response (HTTP HTTP_RESPONSE_CODE_ORDER):
        models::Order successResponse;
        // ... populate response ...
        return successResponse;
    }

};
```
#### User

Create a class that inherits from the generated base class:

```cpp
#include "api/UserApi.h"

class UserImpl : public Api::User {
public:
    void handlePostForUser(const UserPostRequest& params) override {
        // Access request parameters from params struct
        // Implement your logic here
    }

    void handlePostForUsercreateWithArray(const UsercreateWithArrayPostRequest& params) override {
        // Access request parameters from params struct
        // Implement your logic here
    }

    void handlePostForUsercreateWithList(const UsercreateWithListPostRequest& params) override {
        // Access request parameters from params struct
        // Implement your logic here
    }

    void handleDeleteForUserusername(const UserusernameDeleteRequest& params) override {
        // Access request parameters from params struct
        // Implement your logic here
    }

    UserusernameGetResponse handleGetForUserusername(const UserusernameGetRequest& params) override {
        // Access request parameters:
        // Path: params.m_username

        // Implement your business logic here

        // Return success response (HTTP HTTP_RESPONSE_CODE_USER):
        models::User successResponse;
        // ... populate response ...
        return successResponse;
    }

    UserloginGetResponse handleGetForUserlogin(const UserloginGetRequest& params) override {
        // Access request parameters:
        // Query: params.m_username
        // Query: params.m_password

        // Implement your business logic here

        // Return success response (HTTP HTTP_RESPONSE_CODE_PRIMITIVE_STRING):
        std::string successResponse;
        // ... populate response ...
        return successResponse;
    }

    void handleGetForUserlogout() override {
        // Implement your logic here
    }

    void handlePutForUserusername(const UserusernamePutRequest& params) override {
        // Access request parameters from params struct
        // Implement your logic here
    }

};
```

## Running the Server

Here's a complete example of setting up and running the server:

```cpp
#include <httplib.h>
#include <memory>

#include "api/PetApi.h"

#include "api/StoreApi.h"

#include "api/UserApi.h"

#include "api/AuthenticationManager.h"

int main() {
    httplib::Server server;

    // Create authentication manager (required for this API)
    auto authMgr = std::make_shared<MyAuthManager>();

    // Create API implementations

    PetImpl pet;

    StoreImpl store;

    UserImpl user;


    // Register routes

    pet.registerRoutes(server, authMgr);

    store.registerRoutes(server, authMgr);

    user.registerRoutes(server, authMgr);


    // Start server
    std::cout << "Server starting on http://localhost:8080" << std::endl;
    server.listen("localhost", 8080);

    return 0;
}
```

### With Authentication

When authentication is required, you must:
1. Implement the `AuthenticationManager` interface (see Authentication section below)
2. Pass the authentication manager to `registerRoutes()`


## Authentication

This API requires authentication. Implement the `AuthenticationManager` interface to provide your authentication logic:

```cpp
#include "api/AuthenticationManager.h"

class MyAuthManager : public Api::AuthenticationManager {
public:
    bool validateApiKey(const std::string& key) override {
        // Validate API key from header, query, or cookie
        // Example: check against database or cache
        return checkApiKeyInDatabase(key);
    }

    bool validateBearerToken(const std::string& token) override {
        // Validate JWT or other bearer tokens
        // Example: verify signature and expiration
        return jwt::verify(token, secret_key);
    }

    bool validateBasicAuth(const std::string& username, const std::string& password) override {
        // Validate username/password credentials
        // Example: check against user database with hashed passwords
        auto user = findUser(username);
        return user && bcrypt::verify(password, user->passwordHash);
    }

    bool validateOAuth2(const std::string& token, const std::vector<std::string>& scopes) override {
        // Validate OAuth2 token and check required scopes
        // Example: introspect token and verify scopes
        auto introspection = oauthProvider.introspect(token);
        return introspection.active && hasAllScopes(introspection.scopes, scopes);
    }
};
```

### Authentication Flow

1. The server automatically extracts credentials from requests (headers, query params, cookies)
2. Before calling your handler, it validates credentials using your `AuthenticationManager`
3. If validation fails, the server returns HTTP 401 Unauthorized automatically
4. If validation succeeds, your handler is called

### Security Schemes

The generated code supports:
- **API Key**: Header, query parameter, or cookie-based authentication
- **Bearer Token**: Authorization header with "Bearer" scheme (e.g., JWT)
- **Basic Auth**: HTTP Basic authentication (username:password)
- **OAuth2**: OAuth 2.0 token-based authentication with scope validation


## Error Handling

### Response Variants

Each API endpoint that returns data uses `std::variant` to represent multiple possible response types (success and errors):

```cpp
// Example: endpoint returns success (User) or errors (NotFound, ServerError)
using GetUserResponse = std::variant<User, NotFound, ServerError>;

GetUserResponse handleGetUser(const GetUserRequest& params) override {
    if (userExists(params.m_userId)) {
        User user = fetchUser(params.m_userId);
        return user;  // Automatically sets HTTP 200
    } else {
        NotFound error;
        error.setMessage("User not found");
        return error;  // Automatically sets HTTP 404
    }
}
```

The server automatically:
- Detects which type is returned from the variant
- Sets the appropriate HTTP status code
- Serializes the response to JSON

### HTTP Status Codes

Status codes are automatically set based on the response type you return. Each model type is associated with a specific HTTP status code defined in your OpenAPI specification.

**Optimized Status Code Constants:**
The generator only creates HTTP status code constants (e.g., `HTTP_RESPONSE_CODE_200`, `HTTP_RESPONSE_CODE_404`) for codes actually used by your API operations. This reduces code bloat and compilation time compared to generating all possible HTTP status codes.

### Parameter Validation

The generated code automatically validates:
- **Required parameters**: Returns HTTP 400 if missing
- **Type conversion**: Returns HTTP 400 if parameter cannot be converted to expected type
- **JSON parsing**: Returns HTTP 400 if request body is invalid JSON

Custom validation logic should be implemented in your handler methods.

### Working with Optional Parameters

Optional parameters and model fields use `std::optional`:

```cpp
void handleRequest(const RequestParams& params) override {
    // Check if optional query parameter is present
    if (params.m_optionalParam) {
        auto value = *params.m_optionalParam;  // Dereference to get value
        // Use value...
    }

    // Check if optional request body is present
    if (params.m_request) {
        auto body = *params.m_request;  // Dereference to get body
        // Use body...
    }
}
```

## Advanced Features

### Parameter Serialization Styles

The generator supports various parameter serialization styles as defined in OpenAPI:

- **simple**: Comma-separated values (default for path/header)
- **form**: Ampersand-separated values (default for query)
- **spaceDelimited**: Space-separated values
- **pipeDelimited**: Pipe-separated values
- **deepObject**: Nested object notation for query parameters

These are automatically handled during parameter parsing.

### Enum Handling

All generated enums automatically include an `UNSPECIFIED` value as the first enum entry for safe initialization:

```cpp
enum class Status {
    UNSPECIFIED = 0,  // Added automatically for safety
    PENDING,
    APPROVED,
    REJECTED
};

// Safe default initialization
Status status;  // Defaults to UNSPECIFIED (0)

// Explicit initialization
Status activeStatus = Status::APPROVED;

// Enum serialization/deserialization
// UNSPECIFIED is not a valid API value and indicates uninitialized state
```

**Why UNSPECIFIED?**
- Provides a safe default value for uninitialized enums
- Prevents undefined behavior from using uninitialized enum values
- Makes it clear when an enum hasn't been set vs. having a valid API value
- Does not appear in OpenAPI spec - internal C++ implementation detail

### Union Types (anyOf/oneOf)

When your OpenAPI spec uses `anyOf` or `oneOf`, the generated code uses `std::variant`:

```cpp
// OpenAPI: { "anyOf": [{"type": "string"}, {"type": "number"}] }
using MyUnionType = std::variant<std::string, double>;

// In your model:
MyUnionType value;

// Use std::visit to handle different types:
std::visit([](const auto& v) {
    using T = std::decay_t<decltype(v)>;
    if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "String: " << v << std::endl;
    } else if constexpr (std::is_same_v<T, double>) {
        std::cout << "Number: " << v << std::endl;
    }
}, value);
```

## Additional Resources

- [cpp-httplib Documentation](https://github.com/yhirose/cpp-httplib)
- [nlohmann/json Documentation](https://github.com/nlohmann/json)
- [OpenAPI Generator Documentation](https://openapi-generator.tech/docs/generators/cpp-httplib-server)
- [OpenAPI Specification](https://swagger.io/specification/)

- [cpp-httplib Documentation](https://github.com/yhirose/cpp-httplib)
- [nlohmann/json Documentation](https://github.com/nlohmann/json)
- [OpenAPI Generator Documentation](https://openapi-generator.tech/docs/generators/)
