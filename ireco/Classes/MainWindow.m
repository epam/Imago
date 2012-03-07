//
//  MainWindow.m
//  ireco
//
//  Created by Karulin Boris on 13.10.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import "MainWindow.h"

@implementation ViewToObserve

@synthesize viewToObserve;
@synthesize controllerThatObserves;

- (void)dealloc
{
   [viewToObserve release];
   [super dealloc];
}

- (id) initWithData:(UIView *)view andDelegate:(id)delegate {
   self = [super init];
   if(self) {
      viewToObserve = view;
      controllerThatObserves = delegate;
   }
   
   return self;
}

- (void)sendEvent:(UIEvent *)event 
{
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
}

@end

@implementation MainWindow

@synthesize viewObj;
@synthesize viewsObjs;

- (void)startObserveView:(UIView *)view andDelegate:(id)delegate
{
    if(self.viewsObjs == nil) {
       self.viewsObjs = [[NSMutableArray alloc] init ]; 
    }
    [self.viewsObjs addObject:[[ViewToObserve alloc] initWithData:view andDelegate:delegate ] ];
    self.viewObj = [[ViewToObserve alloc] initWithData:view andDelegate:delegate ]; 
   
}

- (void)dealloc
{
   if(self.viewsObjs != nil) {
      [viewsObjs release];
   }
   [viewObj release];
   [super dealloc];
}

/*- (void)forwardMove:(id)touch 
{
    [controllerThatObserves userDidTouchMove:touch];
}*/

- (void)sendEvent:(UIEvent *)event 
{
   [super sendEvent:event];
   if (viewsObjs == nil)
       return;
   for (ViewToObserve *view in viewsObjs) {
      [view sendEvent:event];
   }
}

@end
