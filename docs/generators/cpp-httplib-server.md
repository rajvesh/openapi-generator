# C++ httplib Server Generator - Complete Documentation

## Overview

The `cpp-httplib-server` generator creates a modern C++17 server implementation using the [cpp-httplib](https://github.com/yhirose/cpp-httplib) library. It generates type-safe server stubs from OpenAPI 3.0 specifications with full support for `std::optional`, `std::variant`, scoped enums, and comprehensive JSON serialization via nlohmann::json.

**Key Features:**
- ✅ Complete OpenAPI 3.0 support (schemas, parameters, requests, responses)
- ✅ Type-safe C++17 with modern STL containers
- ✅ Automatic JSON serialization/deserialization
- ✅ Support for oneOf/anyOf (variants), enums, inheritance
- ✅ Header-only dependencies (FetchContent integration)

---

## Supported OpenAPI Features

### 1. Data Types & Mappings

#### Primitive Types

| OpenAPI Type | Format | C++ Type | Notes |
|--------------|--------|----------|-------|
| `string` | - | `std::string` | UTF-8 |
| `string` | `byte` | `std::string` | Base64 encoded |
| `string` | `binary` | `std::string` | Raw binary |
| `string` | `date` | `std::string` | ISO 8601 date |
| `string` | `date-time` | `std::string` | ISO 8601 datetime |
| `integer` | `int32` | `int32_t` | 32-bit signed |
| `integer` | `int64` | `int64_t` | 64-bit signed |
| `integer` | - | `int` | Default integer |
| `number` | `float` | `float` | 32-bit float |
| `number` | `double` | `double` | 64-bit float |
| `number` | - | `double` | Default number |
| `boolean` | - | `bool` | true/false |

**Example OpenAPI:**
```json
{
  "components": {
    "schemas": {
      "PrimitiveTypes": {
        "type": "object",
        "properties": {
          "name": {
            "type": "string"
          },
          "age": {
            "type": "integer",
            "format": "int32"
          },
          "score": {
            "type": "number",
            "format": "double"
          },
          "active": {
            "type": "boolean"
          }
        }
      }
    }
  }
}
```

**Generated C++ (Header):**
```cpp
namespace models {

class PrimitiveTypes
{
public:
    PrimitiveTypes();
    virtual ~PrimitiveTypes() = default;

    [[nodiscard]] std::string getName() const;
    void setName(const std::string& name);
    [[nodiscard]] int32_t getAge() const;
    void setAge(const int32_t& age);
    [[nodiscard]] double getScore() const;
    void setScore(const double& score);
    [[nodiscard]] bool getActive() const;
    void setActive(const bool& active);

    // NLOHMANN JSON serialization macro (inside class for private member access)
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(PrimitiveTypes, name, age, score, active)

private:
    std::string name;
    int32_t age;
    double score;
    bool active;
};

} // namespace models
```

**Generated C++ (Source):**
```cpp
namespace models {

PrimitiveTypes::PrimitiveTypes()
: name("")
, age(0)
, score(0.0)
, active(false)
{
}

std::string PrimitiveTypes::getName() const { return name; }
void PrimitiveTypes::setName(const std::string& nameObj) { name = nameObj; }
// ... other getters/setters
}
```

---

#### Arrays (std::vector)

Arrays map to `std::vector<T>` with support for nested arrays and any element type.

**Example:**
```json
{
  "ArrayTypes": {
    "type": "object",
    "properties": {
      "stringArray": {
        "type": "array",
        "items": {
          "type": "string"
        }
      },
      "objectArray": {
        "type": "array",
        "items": {
          "$ref": "#/components/schemas/Pet"
        }
      },
      "nestedArray": {
        "type": "array",
        "items": {
          "type": "array",
          "items": {
            "type": "integer"
          }
        }
      }
    }
  }
}
```

**Generated:**
```cpp
class ArrayTypes {
private:
    std::vector<std::string> stringArray;
    std::vector<Pet> objectArray;  // Works with complex types
    std::vector<std::vector<int>> nestedArray;  // Nested vectors supported
};
```

**JSON Serialization (Automatic):**
```json
{
  "stringArray": ["a", "b", "c"],
  "objectArray": [{"id": 1, "name": "Fluffy"}, {"id": 2, "name": "Spot"}],
  "nestedArray": [[1, 2], [3, 4]]
}
```

---

#### Enums (enum class with Conversions)

Enums generate as C++11 scoped enums (`enum class`) with custom string conversion functions.

**Example:**
```json
{
  "Status": {
    "type": "string",
    "enum": [
      "pending",
      "approved",
      "rejected"
    ]
  }
}
```

**Generated C++ (Header):**
```cpp
class MyModel {
public:
    enum class StatusEnum {
        UNSPECIFIED,  // Auto-generated default
        PENDING,
        APPROVED,
        REJECTED
    };

    // Conversion functions (declarations in header, definitions in .cpp)
    static std::string StatusEnumToString(StatusEnum value);
    static StatusEnum StatusEnumFromString(const std::string& str);

    // Friend inline functions for JSON serialization (required for ADL)
    friend inline void to_json(nlohmann::json& j, const StatusEnum& e)
    {
        j = StatusEnumToString(e);
    }

    friend inline void from_json(const nlohmann::json& j, StatusEnum& e)
    {
        e = StatusEnumFromString(j.get<std::string>());
    }

    // Optional enum support
    friend inline void to_json(nlohmann::json& j, const std::optional<StatusEnum>& opt)
    {
        if (opt.has_value())
        {
            j = StatusEnumToString(opt.value());
        }
        else
        {
            j = nullptr;
        }
    }

    friend inline void from_json(const nlohmann::json& j, std::optional<StatusEnum>& opt)
    {
        if (j.is_null())
        {
            opt = std::nullopt;
        }
        else
        {
            opt = StatusEnumFromString(j.get<std::string>());
        }
    }

private:
    StatusEnum status;
};
```

**Generated C++ (Source):**
```cpp
std::string MyModel::StatusEnumToString(StatusEnum value)
{
    switch (value)
    {
        case StatusEnum::PENDING: return "pending";
        case StatusEnum::APPROVED: return "approved";
        case StatusEnum::REJECTED: return "rejected";
        default: return {};
    }
}

MyModel::StatusEnum MyModel::StatusEnumFromString(const std::string& str)
{
    if (str == "pending")
    {
        return StatusEnum::PENDING;
    }
    if (str == "approved")
    {
        return StatusEnum::APPROVED;
    }
    if (str == "rejected")
    {
        return StatusEnum::REJECTED;
    }
    throw std::invalid_argument("Invalid enum value");
}
```

**JSON Example:**
```json
{
  "status": "approved"
}
```

---

#### Optional Properties (std::optional)

Optional properties use `std::optional<T>` from C++17.

**Example:**
```json
{
  "User": {
    "type": "object",
    "required": [
      "id",
      "name"
    ],
    "properties": {
      "id": {
        "type": "integer",
        "format": "int64"
      },
      "name": {
        "type": "string"
      },
      "email": {
        "type": "string"
      },
      "age": {
        "type": "integer"
      }
    }
  }
}
```

**Generated:**
```cpp
class User {
public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(User, id, name, email, age)

private:
    int64_t id;                       // Required
    std::string name;                 // Required
    std::optional<std::string> email;  // Optional
    std::optional<int> age;           // Optional
};
```

**JSON Examples:**
```json
// All fields present
{
  "id": 123,
  "name": "Alice",
  "email": "alice@example.com",
  "age": 30
}

// Optional fields missing
{
  "id": 123,
  "name": "Bob"
}

// Optional fields null
{
  "id": 123,
  "name": "Charlie",
  "email": null,
  "age": null
}
```

**Accessing Optional Values:**
```cpp
User user = parseFromJson(jsonString);

// Check if value present
if (user.getEmail().has_value()) {
    std::string email = user.getEmail().value();
    // or: std::string email = *user.getEmail();
}

// With default value
std::string email = user.getEmail().value_or("no-email@example.com");

// Set optional value
user.setEmail("new@example.com");

// Clear optional value
user.setEmail(std::nullopt);
```

---

### 2. Object Composition

#### oneOf Schemas (std::variant)

`oneOf` generates `std::variant<T1, T2, ...>` with custom serialization logic.

**Example (Simple oneOf):**
```json
{
  "StringOrNumber": {
    "oneOf": [
      {
        "type": "string"
      },
      {
        "type": "number"
      }
    ]
  }
}
```

**Generated:**
```cpp
namespace models {

// Type alias for variant
using StringOrNumber = std::variant<std::string, double>;

// Custom inline serialization (must be in header for ADL)
inline void from_json(const nlohmann::json& j, StringOrNumber& obj)
{
    // Try each variant type in order
    try
    {
        obj = j.get<std::string>();
        return;
    }
    catch (const nlohmann::json::exception&)
    {
        // Type mismatch, try next
    }

    try
    {
        obj = j.get<double>();
        return;
    }
    catch (const nlohmann::json::exception&)
    {
        // Type mismatch, try next
    }

    throw nlohmann::json::type_error::create(302,
        "Could not deserialize into any variant type of StringOrNumber", &j);
}

inline void to_json(nlohmann::json& j, const StringOrNumber& obj)
{
    std::visit([&j](const auto& val) { j = nlohmann::json(val); }, obj);
}

} // namespace models
```

**Example (oneOf with Discriminator):**
```json
{
  "components": {
    "schemas": {
      "PaymentMethod": {
        "oneOf": [
          {
            "$ref": "#/components/schemas/CreditCard"
          },
          {
            "$ref": "#/components/schemas/BankAccount"
          }
        ],
        "discriminator": {
          "propertyName": "paymentType",
          "mapping": {
            "credit_card": "#/components/schemas/CreditCard",
            "bank_account": "#/components/schemas/BankAccount"
          }
        }
      },
      "CreditCard": {
        "type": "object",
        "required": [
          "paymentType",
          "cardNumber"
        ],
        "properties": {
          "paymentType": {
            "type": "string"
          },
          "cardNumber": {
            "type": "string"
          }
        }
      },
      "BankAccount": {
        "type": "object",
        "required": [
          "paymentType",
          "accountNumber"
        ],
        "properties": {
          "paymentType": {
            "type": "string"
          },
          "accountNumber": {
            "type": "string"
          }
        }
      }
    }
  }
}
```

**Generated:**
```cpp
using PaymentMethod = std::variant<CreditCard, BankAccount>;

inline void from_json(const nlohmann::json& j, PaymentMethod& obj)
{
    // Check for discriminator property
    if (!j.contains("paymentType"))
    {
        throw nlohmann::json::type_error::create(302,
            "Discriminator property 'paymentType' not found in JSON", &j);
    }

    std::string discriminatorValue = j["paymentType"].get<std::string>();

    // Route based on discriminator value
    if (discriminatorValue == "credit_card")
    {
        obj = j.get<CreditCard>();
        return;
    }
    if (discriminatorValue == "bank_account")
    {
        obj = j.get<BankAccount>();
        return;
    }

    throw nlohmann::json::type_error::create(302,
        "Unknown discriminator value: " + discriminatorValue, &j);
}

inline void to_json(nlohmann::json& j, const PaymentMethod& obj)
{
    std::visit([&j](const auto& val) { j = nlohmann::json(val); }, obj);
}
```

**Using Variants:**
```cpp
// Create variant
PaymentMethod payment = CreditCard{/*...*/};
// or
PaymentMethod payment = BankAccount{/*...*/};

// Access variant (visitor pattern)
std::visit([](const auto& value) {
    using T = std::decay_t<decltype(value)>;
    if constexpr (std::is_same_v<T, CreditCard>) {
        std::cout << "Card: " << value.getCardNumber() << "\n";
    }
    else if constexpr (std::is_same_v<T, BankAccount>) {
        std::cout << "Account: " << value.getAccountNumber() << "\n";
    }
}, payment);

// Check which type
if (std::holds_alternative<CreditCard>(payment)) {
    CreditCard& card = std::get<CreditCard>(payment);
    // ...
}
```

---

#### anyOf Schemas

`anyOf` is implemented identically to `oneOf` using `std::variant`.

---

#### allOf Schemas (Inheritance)

`allOf` with single `$ref` generates C++ inheritance.

**Example:**
```json
{
  "components": {
    "schemas": {
      "Animal": {
        "type": "object",
        "required": [
          "name",
          "type"
        ],
        "properties": {
          "name": {
            "type": "string"
          },
          "type": {
            "type": "string"
          }
        }
      },
      "Dog": {
        "allOf": [
          {
            "$ref": "#/components/schemas/Animal"
          },
          {
            "type": "object",
            "required": [
              "breed"
            ],
            "properties": {
              "breed": {
                "type": "string"
              },
              "barkVolume": {
                "type": "integer"
              }
            }
          }
        ]
      }
    }
  }
}
```

**Generated:**
```cpp
class Animal {
public:
    Animal();
    virtual ~Animal() = default;

    [[nodiscard]] std::string getName() const;
    void setName(const std::string& name);
    [[nodiscard]] std::string getType() const;
    void setType(const std::string& type);

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Animal, name, type)

private:
    std::string name;
    std::string type;
};

class Dog : public Animal {
public:
    Dog();
    virtual ~Dog() = default;

    [[nodiscard]] std::string getBreed() const;
    void setBreed(const std::string& breed);
    [[nodiscard]] int getBarkVolume() const;
    void setBarkVolume(const int& barkVolume);

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Dog, breed, barkVolume)

private:
    std::string breed;
    int barkVolume;
};
```

**JSON Serialization:**
```json
{
  "name": "Buddy",
  "type": "dog",
  "breed": "Golden Retriever",
  "barkVolume": 8
}
```

**Note on Serialization:**
- Each class only serializes its own fields
- Parent fields must be serialized separately if needed
- For complete serialization, manually combine parent + child fields

---

### 3. API Operations

#### Path Parameters

**Example:**
```json
{
  "paths": {
    "/pets/{petId}": {
      "get": {
        "operationId": "getPetById",
        "parameters": [
          {
            "name": "petId",
            "in": "path",
            "required": true,
            "schema": {
              "type": "integer",
              "format": "int64"
            }
          }
        ]
      }
    }
  }
}
```

**Generated Request Struct:**
```cpp
struct GetPetByIdRequest {
    int64_t m_petId; // Path parameters (always required)
};
```

**Generated Parsing Function:**
```cpp
bool Pets::parseGetPetByIdParams(const httplib::Request& req,
                                  Pets::GetPetByIdRequest& params,
                                  std::vector<std::string>& paramErrors)
{
    std::vector<std::string> errors;

    // Path Parameters - petId (index: 1)
    if (req.matches.size() < 1 + 1)
    {
        errors.push_back("Missing path parameter 'petId'");
    }
    else
    {
        try
        {
            params.m_petId = std::stoll(req.matches[1]);
        }
        catch (const std::exception& e)
        {
            errors.push_back("Invalid path parameter 'petId': " + std::string(e.what()));
        }
    }

    if (!errors.empty())
    {
        paramErrors = std::move(errors);
        return false;
    }
    return true;
}
```

---

#### Query Parameters

**Example:**
```json
{
  "parameters": [
    {
      "name": "limit",
      "in": "query",
      "schema": {
        "type": "integer",
        "format": "int32"
      }
    },
    {
      "name": "filter",
      "in": "query",
      "required": true,
      "schema": {
        "type": "string"
      }
    }
  ]
}
```

**Generated:**
```cpp
struct ListPetsRequest {
    std::optional<int32_t> m_limit;  // Query Params (optional)
    std::string m_filter;             // Query Params (required)
};

// Parsing:
bool parseListPetsParams(const httplib::Request& req,
                         ListPetsRequest& params,
                         std::vector<std::string>& paramErrors)
{
    std::vector<std::string> errors;

    // Query Parameters - limit
    if (req.has_param("limit"))
    {
        try
        {
            params.m_limit = std::stoi(req.get_param_value("limit"));
        }
        catch (const std::exception& e)
        {
            errors.push_back("Invalid query parameter 'limit': " + std::string(e.what()));
        }
    }

    // Query Parameters - filter
    if (req.has_param("filter"))
    {
        params.m_filter = req.get_param_value("filter");
    }
    else
    {
        errors.push_back("Missing required query parameter: filter");
    }

    if (!errors.empty())
    {
        paramErrors = std::move(errors);
        return false;
    }
    return true;
}
```

**Query Parameter Styles:**
- `form` (default): `?limit=10&filter=active`
- `spaceDelimited`: `?tags=red%20blue%20green`
- `pipeDelimited`: `?tags=red|blue|green`
- `deepObject`: `?person[name]=John&person[age]=30`

---

#### Header Parameters

**Example:**
```json
{
  "parameters": [
    {
      "name": "X-Request-ID",
      "in": "header",
      "required": false,
      "schema": {
        "type": "string"
      }
    }
  ]
}
```

**Generated:**
```cpp
struct MyOperationRequest {
    std::optional<std::string> m_requestId; // HeaderParams (optional)
};

// Parsing:
// Header Parameters - X-Request-ID
if (!req.get_header_value("X-Request-ID").empty())
{
    params.m_requestId = req.get_header_value("X-Request-ID");
}
```

---

#### Request Body

**Example:**
```json
{
  "requestBody": {
    "required": true,
    "content": {
      "application/json": {
        "schema": {
          "$ref": "#/components/schemas/Pet"
        }
      }
    }
  }
}
```

**Generated:**
```cpp
struct CreatePetRequest {
    models::Pet m_request; // Request Body (required)
};

// Parsing:
if (!req.body.empty())
{
    try
    {
        nlohmann::json json = nlohmann::json::parse(req.body);
        from_json(json, params.m_request);
    }
    catch (const std::exception& e)
    {
        errors.push_back("Invalid request body: " + std::string(e.what()));
    }
}
else
{
    errors.push_back("Missing required request body");
}
```

**Optional Request Body:**
```cpp
struct UpdatePetRequest {
    std::optional<models::Pet> m_request; // Request Body (optional)
};

// Parsing:
if (!req.body.empty())
{
    try
    {
        nlohmann::json json = nlohmann::json::parse(req.body);
        models::Pet temp;
        from_json(json, temp);
        params.m_request = temp;
    }
    catch (const std::exception& e)
    {
        errors.push_back("Invalid request body: " + std::string(e.what()));
    }
}
```

---

#### Response Handling

**Single Response:**
```json
{
  "responses": {
    "200": {
      "description": "Success",
      "content": {
        "application/json": {
          "schema": {
            "$ref": "#/components/schemas/Pet"
          }
        }
      }
    }
  }
}
```

**Generated:**
```cpp
using GetPetResponse = models::Pet;

void Pets::handleGetPetResponse(const GetPetResponse& result,
                                httplib::Response& res)
{
    // Single response type
    res.status = HTTP_RESPONSE_CODE_SUCCESS_200;
    nlohmann::json responseJson;
    to_json(responseJson, result);
    res.set_content(responseJson.dump(), "application/json");
}
```

**Multiple Responses (variant):**
```json
{
  "responses": {
    "200": {
      "description": "Success",
      "content": {
        "application/json": {
          "schema": {
            "$ref": "#/components/schemas/Pet"
          }
        }
      }
    },
    "404": {
      "description": "Not Found",
      "content": {
        "application/json": {
          "schema": {
            "$ref": "#/components/schemas/NotFound"
          }
        }
      }
    },
    "500": {
      "description": "Server Error",
      "content": {
        "application/json": {
          "schema": {
            "$ref": "#/components/schemas/Error"
          }
        }
      }
    }
  }
}
```

**Generated:**
```cpp
using GetPetResponse = std::variant<models::Pet,
                                    models::NotFound,
                                    models::Error>;

void Pets::handleGetPetResponse(const GetPetResponse& result,
                                httplib::Response& res)
{
    std::visit([&](const auto& value)
    {
        using T = std::decay_t<decltype(value)>;

        // Success types
        if constexpr (std::is_same_v<T, models::Pet>)
        {
            res.status = HTTP_RESPONSE_CODE_PET_200;
            nlohmann::json responseJson;
            to_json(responseJson, value);
            res.set_content(responseJson.dump(), "application/json");
        }
        // Error types
        else if constexpr (std::is_same_v<T, models::NotFound>)
        {
            res.status = HTTP_RESPONSE_CODE_NOT_FOUND_404;
            nlohmann::json errorJson;
            to_json(errorJson, value);
            res.set_content(errorJson.dump(), "application/json");
        }
        else if constexpr (std::is_same_v<T, models::Error>)
        {
            res.status = HTTP_RESPONSE_CODE_ERROR_500;
            nlohmann::json errorJson;
            to_json(errorJson, value);
            res.set_content(errorJson.dump(), "application/json");
        }
    }, result);
}
```

---

## Code Organization & File Structure

### Generated Directory Layout

```
generated-output/
├── api/
│   ├── PetsApi.h               # API interface (pure virtual methods)
│   ├── PetsApi.cpp             # API implementation (parsing, routing)
│   ├── StoreApi.h
│   ├── StoreApi.cpp
│   └── AuthenticationManager.h  # Security schemes
├── models/
│   ├── Pet.h                   # Model declarations
│   ├── Pet.cpp                 # Model implementations
│   ├── Category.h
│   ├── Category.cpp
│   ├── StringOrNumber.h        # oneOf variant (header-only)
│   └── ...
├── CMakeLists.txt              # Build configuration
├── README.md                   # Usage instructions
└── LICENSE
```

### Header File Structure (models/Pet.h)

```cpp
/**
 * Auto-generated by OpenAPI Generator
 * Do not edit manually
 */

#pragma once

// ============================================
// System headers (sorted alphabetically)
// ============================================
#include <nlohmann/json.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

// ============================================
// Project headers (sorted alphabetically)
// ============================================
#include "Category.h"
#include "Tag.h"

namespace models {

class Pet
{
public:
    // ===== Nested Enums =====
    enum class StatusEnum {
        UNSPECIFIED,
        AVAILABLE,
        PENDING,
        SOLD
    };

    // Enum conversion functions
    static std::string StatusEnumToString(StatusEnum value);
    static StatusEnum StatusEnumFromString(const std::string& str);

    // ===== Constructor & Destructor =====
    Pet();
    virtual ~Pet() = default;

    // ===== Getters and Setters =====
    [[nodiscard]] std::string getName() const;
    void setName(const std::string& name);

    [[nodiscard]] StatusEnum getStatus() const;
    void setStatus(const StatusEnum& status);

    // ===== JSON Serialization =====
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Pet, id, name, category, tags, status)

    // ===== Enum JSON Serialization (friend for ADL) =====
    friend inline void to_json(nlohmann::json& j, const StatusEnum& e)
    {
        j = StatusEnumToString(e);
    }

    friend inline void from_json(const nlohmann::json& j, StatusEnum& e)
    {
        e = StatusEnumFromString(j.get<std::string>());
    }

private:
    int64_t id;
    std::string name;
    Category category;
    std::vector<Tag> tags;
    StatusEnum status;
};

} // namespace models
```

---

### Source File Structure (models/Pet.cpp)

```cpp
/**
 * Auto-generated by OpenAPI Generator
 * Do not edit manually
 */
#include "Pet.h"

namespace models {

// =========================================
// ===== Constructor =====
// =========================================
Pet::Pet()
: id(0)
, name("")
, category()
, tags()
, status(StatusEnum::UNSPECIFIED)
{
}

// =========================================
// ===== Getters =====
// =========================================
int64_t Pet::getId() const
{
    return id;
}

std::string Pet::getName() const
{
    return name;
}

// ... other getters

// =========================================
// ===== Setters =====
// =========================================
void Pet::setId(const int64_t& idObj)
{
    id = idObj;
}

void Pet::setName(const std::string& nameObj)
{
    name = nameObj;
}

// ... other setters

// =========================================
// ===== Enum Conversions =====
// =========================================
std::string Pet::StatusEnumToString(StatusEnum value)
{
    switch (value)
    {
        case StatusEnum::AVAILABLE: return "available";
        case StatusEnum::PENDING: return "pending";
        case StatusEnum::SOLD: return "sold";
        default: return {};
    }
}

Pet::StatusEnum Pet::StatusEnumFromString(const std::string& str)
{
    if (str == "available")
    {
        return StatusEnum::AVAILABLE;
    }
    if (str == "pending")
    {
        return StatusEnum::PENDING;
    }
    if (str == "sold")
    {
        return StatusEnum::SOLD;
    }
    throw std::invalid_argument("Invalid enum value");
}

} // namespace models
```

---

## Advanced Topics

### Argument-Dependent Lookup (ADL)

**What is ADL?**
ADL is a C++ feature where the compiler looks for functions in the namespaces of function arguments.

**Example:**
```cpp
namespace models {
    class Pet { /*...*/ };
    void from_json(const nlohmann::json& j, Pet& pet) { /*...*/ }
}

namespace Api {
    using namespace models; // Enables ADL

    void handleRequest()
    {
        nlohmann::json j;
        Pet pet;

        from_json(j, pet); // Compiler finds models::from_json via ADL!
        // Looks in namespaces of arguments: nlohmann:: and models::
    }
}
```

ADL enables NLOHMANN JSON library to automatically find serialization functions. Calling `j.get<Pet>()` internally uses `from_json(j, pet)` via ADL. Serialization functions are free functions in the same namespace as the type, and `using namespace models;` in API code enables ADL for all model types.

---

### Inline Model Naming

When OpenAPI has inline schemas (not `$ref`), generator creates class names automatically.

**Example:**
```json
{
  "paths": {
    "/test": {
      "get": {
        "operationId": "testQueryParameters",
        "parameters": [
          {
            "name": "deepObject",
            "in": "query",
            "style": "deepObject",
            "schema": {
              "type": "object",
              "properties": {
                "name": {
                  "type": "string"
                },
                "age": {
                  "type": "integer"
                }
              }
            }
          }
        ]
      }
    }
  }
}
```

**Generated Class Name:**
```
TestQueryParametersDeepObjectParameter
^     ^               ^         ^
|     |               |         |
Op    Param           Param     Suffix
Name  Location        Name
```

**Naming Pattern:** `{OperationId}{ParamLocation}{ParamName}Parameter`

**PascalCase Conversion:**
- Input: `test_query_parameters`, `deep_object`
- Output: `TestQueryParametersDeepObjectParameter`

**Special Cases:**
- `200_response` → `200Response` (preserve numeric prefix)
- `deep_obj_baz` → `DeepObjBaz`
- Already PascalCase preserved: `TestCase` → `TestCase`

---

### Build System (CMake)

**Generated CMakeLists.txt:**
```cmake
cmake_minimum_required(VERSION 3.10)
project(openapi_server CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===== Dependencies (FetchContent) =====
include(FetchContent)

# nlohmann_json
FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)

# cpp-httplib
FetchContent_Declare(
    httplib
    URL https://github.com/yhirose/cpp-httplib/archive/v0.15.3.tar.gz
)
FetchContent_MakeAvailable(httplib)

# ===== Library =====
file(GLOB MODEL_SOURCES "models/*.cpp")
file(GLOB API_SOURCES "api/*.cpp")

add_library(cpp_httplib_server_openapi_lib STATIC
    ${MODEL_SOURCES}
    ${API_SOURCES}
)

target_include_directories(cpp_httplib_server_openapi_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(cpp_httplib_server_openapi_lib PUBLIC
    nlohmann_json::nlohmann_json
    httplib::httplib
)

# ===== Optional: Build examples =====
option(BUILD_EXAMPLES "Build example server" OFF)
if(BUILD_EXAMPLES)
    add_executable(example_server main.cpp)
    target_link_libraries(example_server cpp_httplib_server_openapi_lib)
endif()
```

---

## Security Schemes

### API Key Authentication

**OpenAPI:**
```json
{
  "components": {
    "securitySchemes": {
      "api_key": {
        "type": "apiKey",
        "name": "X-API-Key",
        "in": "header"
      }
    }
  },
  "paths": {
    "/pets": {
      "get": {
        "security": [
          {
            "api_key": []
          }
        ]
      }
    }
  }
}
```

**Generated (AuthenticationManager.h):**
```cpp
struct ApiKeyAuth
{
    std::string apiKey;
    std::string headerName = "X-API-Key";

    bool validate(const httplib::Request& req) const
    {
        if (!req.has_header(headerName))
        {
            return false;
        }
        return req.get_header_value(headerName) == apiKey;
    }
};
```

**Usage:**
```cpp
ApiKeyAuth auth;
auth.apiKey = "secret-key-12345";

// In request handler:
if (!auth.validate(req))
{
    res.status = 401;
    res.set_content("{\"error\": \"Unauthorized\"}", "application/json");
    return;
}
```

### HTTP Basic Authentication

**Generated:**
```cpp
struct HttpBasicAuth
{
    std::string username;
    std::string password;

    bool validate(const httplib::Request& req) const
    {
        auto auth = req.get_header_value("Authorization");
        if (auth.empty() || auth.substr(0, 6) != "Basic ")
        {
            return false;
        }

        // Base64 decode and compare
        // Implementation left to user
        return true;
    }
};
```

---

## Best Practices

### 1. Implementing Server Logic

**Generated Interface:**
```cpp
class Pets
{
public:
    virtual GetPetsResponse getPets(const GetPetsRequest& request) = 0;
    virtual CreatePetResponse createPet(const CreatePetRequest& request) = 0;
};
```

**User Implementation:**
```cpp
class PetsApiImpl : public Api::Pets
{
public:
    GetPetsResponse getPets(const GetPetsRequest& request) override
    {
        // Business logic
        std::vector<models::Pet> pets = database.fetchPets(
            request.m_limit.value_or(10),
            request.m_offset.value_or(0)
        );
        return pets;
    }

    CreatePetResponse createPet(const CreatePetRequest& request) override
    {
        // Validation
        if (request.m_request.getName().empty())
        {
            return models::Error{"Name is required", 400};
        }

        // Save to database
        models::Pet saved = database.save(request.m_request);
        return saved;
    }
};
```

### 2. Error Handling

**Using Response Variants:**
```cpp
// Return type: std::variant<Pet, NotFound, Error>
GetPetResponse getPet(const GetPetRequest& req) override
{
    auto pet = database.findById(req.m_petId);

    if (!pet)
    {
        return models::NotFound{"Pet not found"}; // 404
    }

    return *pet; // 200
}
```

**Exception Handling:**
```cpp
CreatePetResponse createPet(const CreatePetRequest& req) override
{
    try
    {
        return database.save(req.m_request);
    }
    catch (const std::runtime_error& e)
    {
        return models::Error{e.what(), 500};
    }
}
```

### 3. Validation

**Parameter Validation:**
```cpp
// Already done in parse functions
bool parseParams(const httplib::Request& req,
                 MyRequest& params,
                 std::vector<std::string>& errors)
{
    // Type conversions, required field checks
    // Errors accumulated in vector
    return errors.empty();
}
```

**Custom Validation:**
```cpp
CreatePetResponse createPet(const CreatePetRequest& req) override
{
    // Business rule validation
    if (req.m_request.getName().length() < 3)
    {
        return models::Error{"Name must be at least 3 characters", 400};
    }

    if (req.m_request.getAge() && *req.m_request.getAge() < 0)
    {
        return models::Error{"Age cannot be negative", 400};
    }

    return database.save(req.m_request);
}
```

---

## Performance Considerations

### Compilation Time
- **NLOHMANN macro:** Template-heavy, increases compilation time
- **Mitigation:** Use forward declarations, split large files
- **Benefit:** Zero runtime overhead, type safety

### Runtime Performance
- **JSON parsing:** nlohmann::json is fast (template metaprogramming)
- **Variant dispatch:** `std::visit` is compile-time resolved (zero overhead)
- **Enum conversions:** Switch statements (optimal)
- **String copies:** Getters return by value (consider `const&` for large strings)

### Memory Usage
- **std::optional:** `sizeof(T) + 1` byte (minimal overhead)
- **std::variant:** `sizeof(largest_alternative) + discriminator`
- **std::vector:** 3 pointers (size, capacity, data) + heap allocation
- **No heap allocations** in request/response structs (stack-based)

---

## Known Limitations

1. **No XML support:** Only `application/json`
2. **No multipart/form-data:** Binary uploads not supported
3. **Limited allOf:** Multiple inheritance not supported (flattens instead)
4. **No discriminator with allOf:** Inheritance doesn't use discriminators
5. **No OpenTelemetry:** No built-in observability

---

## Future Enhancements

- [ ] XML serialization support
- [ ] Multipart form data handling
- [ ] WebSocket support
- [ ] Server-sent events (SSE)
- [ ] Async/await support (coroutines)
- [ ] Built-in metrics and tracing
- [ ] Request/response logging
- [ ] Rate limiting helpers

---

## References

- [cpp-httplib Documentation](https://github.com/yhirose/cpp-httplib)
- [nlohmann/json Documentation](https://json.nlohmann.me/)
- [OpenAPI 3.0 Specification](https://swagger.io/specification/)
- [C++17 Reference](https://en.cppreference.com/w/cpp/17)
- [Argument-Dependent Lookup (ADL)](https://en.cppreference.com/w/cpp/language/adl)
