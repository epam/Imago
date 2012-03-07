//
//  CropView.h
//  ireco
//
//  Created by Boris Karulin on 15.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "MainWindow.h"

enum CropMove {
    MoveLeft = 1,
    MoveRight = 2,
    MoveTop = 4,
    MoveBottom = 8
};

@interface CropView : UIView <TapDetectingWindowDelegate> {
    int cropMove;
    CGRect initialFrame;
    CGRect currentFrame;
}

- (void)setInitialFrame:(CGRect)frame;
- (CGRect)cropRect;

@end
