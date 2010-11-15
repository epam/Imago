//
//  RootViewController.h
//  imago-iphone
//
//  Created by Boris Karulin on 19.10.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioServices.h>

#import "OverlayViewController.h"

@interface RootViewController : UIViewController <UIImagePickerControllerDelegate, OverlayViewControllerDelegate>
{
   UIImageView *imageView;
   UIToolbar *myToolbar;
   
   OverlayViewController *overlayViewController; // the camera custom overlay view
   
   NSMutableArray *capturedImages; // the list of images captures from the camera (either 1 or multiple)
}

@property (nonatomic, retain) IBOutlet UIImageView *imageView;
@property (nonatomic, retain) IBOutlet UIToolbar *myToolbar;

@property (nonatomic, retain) OverlayViewController *overlayViewController;

@property (nonatomic, retain) NSMutableArray *capturedImages;

// toolbar buttons
- (IBAction)photoLibraryAction:(id)sender;
- (IBAction)cameraAction:(id)sender;

@end
