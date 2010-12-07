#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioServices.h>

#import "OverlayViewController.h"
#import "KetcherViewController.h"

@interface MainViewController : UIViewController <UIImagePickerControllerDelegate,
                                                OverlayViewControllerDelegate>
{
    UIImageView *imageView;
    UIToolbar *toolbar;
    
    OverlayViewController *overlayViewController; // the camera custom overlay view
    KetcherViewController *ketcherViewController;

    NSMutableArray *capturedImages; // the list of images captures from the camera (either 1 or multiple)

@private
    UIBarButtonItem *recognizeButton;
}

@property (nonatomic, retain) IBOutlet UIImageView *imageView;
@property (nonatomic, retain) IBOutlet UIToolbar *toolbar;

@property (nonatomic, retain) OverlayViewController *overlayViewController;
@property (nonatomic, retain) KetcherViewController *ketcherViewController;

@property (nonatomic, retain) NSMutableArray *capturedImages;

@property (nonatomic, retain) IBOutlet UIBarButtonItem *recognizeButton;

// toolbar buttons
- (IBAction)photoLibraryAction:(id)sender;
- (IBAction)cameraAction:(id)sender;
// navigation bar
- (IBAction)recognizeAction:(id)sender;

@end

