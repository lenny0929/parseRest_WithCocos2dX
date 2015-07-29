//
//  testRestAPI_mobile_Tests.m
//  testRestAPI-mobile Tests
//
//  Created by lenny on 2015/7/29.
//
//

#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>
#include "HelloWorldScene.h"

@interface testRestAPI_mobile_Tests : XCTestCase

@end

@implementation testRestAPI_mobile_Tests

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample
{
    // This is an example of a functional test case.
    XCTAssert(YES, @"Pass");
}

- (void)testPerformanceExample
{
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
