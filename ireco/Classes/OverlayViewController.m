#import "OverlayViewController.h"

@implementation OverlayViewController

@synthesize delegate, takePictureButton,
            cancelButton, imagePickerController, popoverController;


#pragma mark -
#pragma mark OverlayViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]))
    {
        UIImagePickerController *imagePicker = [[UIImagePickerController alloc] init];
        self.imagePickerController = imagePicker;
        self.imagePickerController.delegate = self;
        [imagePicker release];

        if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
        {
            self.imagePickerController.contentSizeForViewInPopover = CGSizeMake(320, 480);
            UIPopoverController *popover = [[UIPopoverController alloc] initWithContentViewController:imagePicker];
            self.popoverController = popover;
            self.popoverController.delegate = self;
            [self.popoverController setPopoverContentSize:(CGSizeMake(320, 480))];
            [popover release];
        }

    }
    return self;
}

- (void)viewDidUnload
{
    self.takePictureButton = nil;
    self.cancelButton = nil;
}

- (void)dealloc
{	
    [takePictureButton release];
    [cancelButton release];
    
    [imagePickerController release];

    [super dealloc];
}

- (void)setupImagePicker:(UIImagePickerControllerSourceType)sourceType
{
    self.imagePickerController.sourceType = sourceType;
}

// called when the parent application receives a memory warning
- (void)didReceiveMemoryWarning
{
    // we have been warned that memory is getting low, stop all timers
    //
    [super didReceiveMemoryWarning];
}

// update the UI after an image has been chosen or picture taken
//
- (void)finishAndUpdate
{
    [self.delegate didFinishWithCamera];  // tell our delegate we are done with the camera

    // restore the state of our overlay toolbar buttons
    self.cancelButton.enabled = YES;
    self.takePictureButton.enabled = YES;
}


#pragma mark -
#pragma mark Camera Actions

- (IBAction)done:(id)sender
{
    // dismiss the camera
    [self finishAndUpdate];
}

- (IBAction)takePhoto:(id)sender
{
    [self.imagePickerController takePicture];
}


#pragma mark -
#pragma mark UIImagePickerControllerDelegate

// this get called when an image has been chosen from the library or taken from the camera
//
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    UIImage *image = [info valueForKey:UIImagePickerControllerOriginalImage];
    
    // give the taken picture to our delegate
    if (self.delegate)
        [self.delegate didTakePicture:image];
    
    [self finishAndUpdate];
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    [self.delegate didFinishWithCamera];    // tell our delegate we are finished with the picker
}



@end

