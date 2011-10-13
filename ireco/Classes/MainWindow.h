//
//  MainWindow.h
//  ireco
//
//  Created by Karulin Boris on 13.10.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol TapDetectingWindowDelegate
- (void)userDidTouchMove:(UITouch *)touch;
- (void)userDidTouchStart:(UITouch *)touch;
- (void)userDidTouchEnd;
@end

@interface MainWindow : UIWindow {
    UIView *viewToObserve;
    id <TapDetectingWindowDelegate> controllerThatObserves;
}
@property (nonatomic, retain) UIView *viewToObserve;
@property (nonatomic, assign) id <TapDetectingWindowDelegate> controllerThatObserves;

- (void)startObserveView:(UIView *)view andDelegate:(id)delegate;

@end
