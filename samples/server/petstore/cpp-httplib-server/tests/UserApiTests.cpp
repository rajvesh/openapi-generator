// gtest unit tests for UserApi
#include <gtest/gtest.h>
#include "api/UserApi.h"
#include <httplib.h>
#include <nlohmann/json.hpp>
using namespace api;

class MockUserApi : public User {
public:
    void handlePostForUser(const PostRequestForUser& params) override {}
    void handlePostForUserCreateWithArray(const PostRequestForUserCreateWithArray& params) override {}
    void handlePostForUserCreateWithList(const PostRequestForUserCreateWithList& params) override {}
    void handleDeleteForUserusername() override {}
    GetResponseForUserusername handleGetForUserusername() override { return sample::models::User(); }
    GetResponseForUserLogin handleGetForUserLogin(const GetRequestForUserLogin&) override { return std::string("token"); }
    void handleGetForUserLogout() override {}
    void handlePutForUserusername(const PutRequestForUserusername&) override {}
};

TEST(UserApiTest, HandlerInvocation) {
    MockUserApi api;
    User::PostRequestForUser req;
    api.handlePostForUser(req);
    User::PostRequestForUserCreateWithArray req2;
    api.handlePostForUserCreateWithArray(req2);
    User::PostRequestForUserCreateWithList req3;
    api.handlePostForUserCreateWithList(req3);
    api.handleDeleteForUserusername();
    auto resp4 = api.handleGetForUserusername();
    EXPECT_TRUE(std::holds_alternative<sample::models::User>(resp4));
    User::GetRequestForUserLogin req5;
    req5.m_username = "user";
    req5.m_password = "pass";
    auto resp5 = api.handleGetForUserLogin(req5);
    EXPECT_TRUE(std::holds_alternative<std::string>(resp5));
    api.handleGetForUserLogout();
    User::PutRequestForUserusername req6;
    api.handlePutForUserusername(req6);
}

TEST(UserApiTest, ParsePostRequestForUser) {
    httplib::Request req;
    nlohmann::json j = { {"id", 1}, {"username", "user"} };
    req.body = j.dump();
    auto params = User::parsePostRequestForUser(req);
    ASSERT_TRUE(params.m_request.has_value());
    EXPECT_EQ(params.m_request->getId(), 1);
}

TEST(UserApiTest, HandleGetResponseForUserusername) {
    httplib::Response res;
    sample::models::User user;
    user.setId(2);
    User::GetResponseForUserusername result = user;
    User::handleGetResponseForUserusername(result, res);
    nlohmann::json j = nlohmann::json::parse(res.body);
    EXPECT_EQ(j["id"], 2);
}

TEST(UserApiTest, ParseGetRequestForUserLogin) {
    httplib::Request req;
    req.params.emplace("username", "user");
    req.params.emplace("password", "pass");
    auto params = User::parseGetRequestForUserLogin(req);
    EXPECT_EQ(params.m_username, "user");
    EXPECT_EQ(params.m_password, "pass");
}

TEST(UserApiTest, HandleGetResponseForUserLogin) {
    httplib::Response res;
    User::GetResponseForUserLogin result = std::string("token");
    User::handleGetResponseForUserLogin(result, res);
    EXPECT_EQ(res.body, "token");
}

TEST(UserApiTest, ParsePutRequestForUserusername) {
    httplib::Request req;
    nlohmann::json j = { {"id", 3}, {"username", "user3"} };
    req.body = j.dump();
    auto params = User::parsePutRequestForUserusername(req);
    ASSERT_TRUE(params.m_request.has_value());
    EXPECT_EQ(params.m_request->getId(), 3);
}
// ...end of UserApi tests...
