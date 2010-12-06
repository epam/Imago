#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioServices.h>

#import "OverlayViewController.h"

@interface MainViewController : UIViewController <UIImagePickerControllerDelegate,
                                                OverlayViewControllerDelegate>
{
    UIImageView *imageView;
    UIToolbar *toolbar;
    
    OverlayViewController *overlayViewController; // the camera custom overlay view

    NSMutableArray *capturedImages; // the list of images captures from the camera (either 1 or multiple)
}

@property (nonatomic, retain) IBOutlet UIImageView *imageView;
@property (nonatomic, retain) IBOutlet UIToolbar *toolbar;

@property (nonatomic, retain) OverlayViewController *overlayViewController;

@property (nonatomic, retain) NSMutableArray *capturedImages;

// toolbar buttons
- (IBAction)photoLibraryAction:(id)sender;
- (IBAction)cameraAction:(id)sender;

@end

