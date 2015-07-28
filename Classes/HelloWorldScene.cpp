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

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
        origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

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
