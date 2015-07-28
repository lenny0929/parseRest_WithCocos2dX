#include "HelloWorldScene.h"
#include <vector>
#include "json/rapidjson.h"
#include "json/document.h"

using namespace std;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()) {
        return false;
    }

    // Post 範例
    HttpRequest* request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::POST);
    request->setUrl("https://api.parse.com/1/classes/sampleTable");

    vector<string> header;
    header.push_back("X-Parse-Application-Id: wCq2Ojdxj0aNdccb94sSr6Ke3uryqsO6spkkZKkd");
    header.push_back("X-Parse-REST-API-Key: Vp6OGjqqV1XNAbmRWzL2EylDVFs0TeULO5EQDDSR");
    header.push_back("Content-Type: application/json");
    request->setHeaders(header);

    auto data = "{\"ColNum\":100, \"ColString\":\"ABC\"}";
    const char* buffer = data;
    request->setRequestData(buffer, strlen(buffer));

    request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpRequestPostCompleted, this));
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();

    // Get 範例
    HttpRequest* getRequest = new HttpRequest();
    getRequest->setUrl("https://api.parse.com/1/classes/sampleTable/qJx3oElFX9");
    getRequest->setHeaders(header);
    getRequest->setRequestType(HttpRequest::Type::GET);
    getRequest->setResponseCallback(CC_CALLBACK_2(HelloWorld::onHttpRequestGetCompleted, this));
    HttpClient::getInstance()->send(getRequest);
    getRequest->release();

    return true;
}
void HelloWorld::onHttpRequestGetCompleted(HttpClient* sender, HttpResponse* response)
{

    if (response->isSucceed()) {
        CCLOG("Get success");

        std::vector<char>* buffer = response->getResponseData();
        std::string res;
        res.insert(res.begin(), buffer->begin(), buffer->end());

        rapidjson::Document d;
        d.Parse<0>(res.c_str());

        printf("%s\n", d["ColString"].GetString());
    }
}
void HelloWorld::onHttpRequestPostCompleted(HttpClient* sender, HttpResponse* response)
{

    if (response->isSucceed()) {
        CCLOG("Post success");
    }
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
