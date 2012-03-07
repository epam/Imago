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

@interface ViewToObserve : NSObject
{
   UIView *viewToObserve;
   id <TapDetectingWindowDelegate> controllerThatObserves;
} 
@property (nonatomic, retain) UIView *viewToObserve;
@property (nonatomic, assign) id <TapDetectingWindowDelegate> controllerThatObserves;
@end

@interface MainWindow : UIWindow {
   NSMutableArray *viewsObjs;
   ViewToObserve *viewObj; 
}
@property (nonatomic, retain) ViewToObserve *viewObj;
@property (nonatomic, retain) NSMutableArray *viewsObjs;

- (void)startObserveView:(UIView *)view andDelegate:(id)delegate;

@end
