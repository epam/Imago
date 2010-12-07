//
//  Recognizer.h
//  ireco
//
//  Created by Boris Karulin on 07.12.10.
//  Copyright 2010 Scite. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface Recognizer : NSObject
{

@private
   UIImage *image;
}

@property (nonatomic, retain) UIImage *image;

- (NSString *)recognize;
+ (Recognizer *)recognizerWithImage:(UIImage *)image;

@end
