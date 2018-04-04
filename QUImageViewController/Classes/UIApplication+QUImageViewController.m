//
//  UIApplication+QUImageViewController.m
//  Riposte
//
//  Created by Jared on 4/3/14.
//  Copyright (c) 2018 Eureka, TS. All rights reserved.
//

#import "UIApplication+QUImageViewController.h"

@implementation UIApplication (QUImageViewController)

- (BOOL)QU_usesViewControllerBasedStatusBarAppearance {
    static dispatch_once_t once;
    static BOOL viewControllerBased;
    dispatch_once(&once, ^ {
        NSString *key = @"UIViewControllerBasedStatusBarAppearance";
        id object = [[NSBundle mainBundle] objectForInfoDictionaryKey:key];
        if (!object) {
            viewControllerBased = YES;
        } else {
            viewControllerBased = [object boolValue];
        }
    });
    return viewControllerBased;
}

@end
