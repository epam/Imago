//
//  MainWindow.m
//  ireco
//
//  Created by Karulin Boris on 13.10.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "MainWindow.h"

@implementation MainWindow

@synthesize viewToObserve;
@synthesize controllerThatObserves;

- (void)startObserveView:(UIView *)view andDelegate:(id)delegate
{
    self.viewToObserve = view;
    self.controllerThatObserves = delegate;
}

- (void)dealloc
{
    [viewToObserve release];
    [super dealloc];
}

/*- (void)forwardMove:(id)touch 
{
    [controllerThatObserves userDidTouchMove:touch];
}*/

- (void)sendEvent:(UIEvent *)event 
{
    [super sendEvent:event];
    if (viewToObserve == nil || controllerThatObserves == nil)
        return;
    NSSet *touches = [event allTouches];
    if (touches.count != 1)
        return;
    UITouch *touch = touches.anyObject;
    if (touch.view != nil && [touch.view isDescendantOfView:viewToObserve] == NO)
        return;
    if (touch.phase == UITouchPhaseBegan)
        [controllerThatObserves userDidTouchStart:touch];
    else if (touch.phase == UITouchPhaseMoved)
        [controllerThatObserves userDidTouchMove:touch];
    else if (touch.phase == UITouchPhaseEnded || touch.phase == UITouchPhaseCancelled)
        [controllerThatObserves userDidTouchEnd];

    /*
    NSArray *pointArray = [NSArray arrayWithObjects:[NSString stringWithFormat:@"%f", tapPoint.x],
                           [NSString stringWithFormat:@"%f", tapPoint.y], nil];
    if (touch.tapCount == 1) {
        [self performSelector:@selector(forwardTap:) withObject:pointArray afterDelay:0.5];
    }
    else if (touch.tapCount > 1) {
        [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(forwardTap:) object:pointArray];
    }
     */
}

@end
