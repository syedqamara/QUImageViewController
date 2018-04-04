//
//  QUSimpleImageDownloader.h
//  
//
//  Created by Syed Qamar Abbas on 3/2/14.
//  Copyright (c) 2018 Eureka, TS. All rights reserved.
//

@import Foundation;
@import UIKit;
@interface QUSimpleImageDownloader : NSObject

+ (NSURLSessionDataTask *)downloadImageForURL:(NSURL *)imageURL
                                 canonicalURL:(NSURL *)canonicalURL
                                   completion:(void(^)(UIImage *image))completion;

@end
