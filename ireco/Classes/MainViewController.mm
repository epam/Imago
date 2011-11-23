#import "MainViewController.h"

@implementation MainViewController

@synthesize imageView, scrollView, toolbar, overlayViewController, ketcherViewController, capturedImage, recognizeButton;


#pragma mark -
#pragma mark View Controller

- (void)viewDidLoad
{
    OverlayViewController *overlay = [[OverlayViewController alloc] initWithNibName:@"OverlayViewController" bundle:nil];
    self.overlayViewController = overlay;

    // as a delegate we will be notified when pictures are taken and when to dismiss the image picker
    self.overlayViewController.delegate = self;
    [overlay release];

    KetcherViewController *ketcher = [[KetcherViewController alloc] initWithNibName:@"KetcherViewController" bundle:nil];
    self.ketcherViewController = ketcher;
    [ketcher release];

    self.scrollView.maximumZoomScale = 4.0;
    self.scrollView.minimumZoomScale = 1.0;

    self.capturedImage = nil;

    if (![UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera])
    {
        // camera is not on this device, don't show the camera button
        NSMutableArray *toolbarItems = [NSMutableArray arrayWithCapacity:self.toolbar.items.count];
        [toolbarItems addObjectsFromArray:self.toolbar.items];
        [toolbarItems removeObjectAtIndex:2];
        [self.toolbar setItems:toolbarItems animated:NO];
    } 
}

- (void)viewWillAppear:(BOOL)animated
{
}

- (void)viewDidUnload
{
    self.imageView = nil;
    self.toolbar = nil;
    
    self.overlayViewController = nil;
    self.capturedImage = nil;
}

- (void)dealloc
{	
   [imageView release];
   [toolbar release];
    
   [overlayViewController release];
   [ketcherViewController release];
   [capturedImage release];
    
   [super dealloc];
}

#pragma mark -
-(UIImage*)imageRotatedByRadians:(UIImage*)anImage:(CGFloat)radians 
{   
    // calculate the size of the rotated view's containing box for our drawing space
    UIView *rotatedViewBox = [[UIView alloc] initWithFrame:CGRectMake(0,0,anImage.size.width, anImage.size.height)];
    CGAffineTransform t = CGAffineTransformMakeRotation(radians);
    rotatedViewBox.transform = t;
    CGSize rotatedSize = rotatedViewBox.frame.size;
    [rotatedViewBox release];
    
    // Create the bitmap context
    UIGraphicsBeginImageContext(rotatedSize);
    CGContextRef bitmap = UIGraphicsGetCurrentContext();
    
    // Move the origin to the middle of the image so we will rotate and scale around the center.
    CGContextTranslateCTM(bitmap, rotatedSize.width/2, rotatedSize.height/2);
    
    //   // Rotate the image context
    CGContextRotateCTM(bitmap, radians);
    
    // Now, draw the rotated/scaled image into the context
    CGContextScaleCTM(bitmap, 1.0, -1.0);
    CGContextDrawImage(bitmap, CGRectMake(-anImage.size.width / 2, -anImage.size.height / 2, anImage.size.width, anImage.size.height), [anImage CGImage]);
    
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    
    return newImage;
} 

-(UIImage*)prepareImage:(UIImage*)anImage
{
    if (anImage.imageOrientation == 0)
        return anImage;
    else if (anImage.imageOrientation == 3) {
        UIImage* sourceImage = anImage; 
        
        CGFloat targetWidth = anImage.size.height;
        CGFloat targetHeight = anImage.size.width;
        
        CGImageRef imageRef = [sourceImage CGImage];
        CGBitmapInfo bitmapInfo = CGImageGetBitmapInfo(imageRef);
        CGColorSpaceRef colorSpaceInfo = CGImageGetColorSpace(imageRef);
        
        if (bitmapInfo == kCGImageAlphaNone) {
            bitmapInfo = kCGImageAlphaNoneSkipLast;
        }
        
        CGContextRef bitmap;
        bitmap = CGBitmapContextCreate(NULL, targetWidth, targetHeight, CGImageGetBitsPerComponent(imageRef), CGImageGetBytesPerRow(imageRef), colorSpaceInfo, bitmapInfo);
        
        CGContextDrawImage(bitmap, CGRectMake(0, 0, targetWidth, targetHeight), imageRef);
        
        CGImageRef ref = CGBitmapContextCreateImage(bitmap);
        UIImage* newImage = [UIImage imageWithCGImage:ref];
        
        CGContextRelease(bitmap);
        CGImageRelease(ref);
        
        return newImage; 
    } else {
        printf("Orientation != {3, 0}");
        return anImage;
    }
}

/*
-(UIImage*)rotateImage:(UIImage*)anImage:(int)orientation
{
    UIImage* sourceImage = anImage; 
        
    CGFloat targetWidth = anImage.size.width;
    CGFloat targetHeight = anImage.size.height;
    
    CGImageRef imageRef = [sourceImage CGImage];
    CGBitmapInfo bitmapInfo = CGImageGetBitmapInfo(imageRef);
    CGColorSpaceRef colorSpaceInfo = CGImageGetColorSpace(imageRef);
    
    if (bitmapInfo == kCGImageAlphaNone) {
        bitmapInfo = kCGImageAlphaNoneSkipLast;
    }
    
    CGContextRef bitmap;
    bitmap = CGBitmapContextCreate(NULL, targetWidth, targetHeight, CGImageGetBitsPerComponent(imageRef), CGImageGetBytesPerRow(imageRef), colorSpaceInfo, bitmapInfo);
   
    if (orientation == 0) {
        CGContextRotateCTM (bitmap, M_PI/2);
        CGContextTranslateCTM (bitmap, 0, -targetHeight);        
    } else {
        CGContextRotateCTM (bitmap, -M_PI/2);
        CGContextTranslateCTM (bitmap, -targetWidth, 0);
    }
    
    CGContextDrawImage(bitmap, CGRectMake(0, 0, targetWidth, targetHeight), imageRef);
    CGImageRef ref = CGBitmapContextCreateImage(bitmap);
    UIImage* newImage = [UIImage imageWithCGImage:ref];
    
    CGContextRelease(bitmap);
    CGImageRelease(ref);
    
    return newImage; 
}
*/
#pragma mark -
#pragma mark Toolbar Actions

- (void)showImagePicker:(UIImagePickerControllerSourceType)sourceType fromButton:(id)button
{
    if ([UIImagePickerController isSourceTypeAvailable:sourceType])
    {
        [self.overlayViewController setupImagePicker:sourceType];
        if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
        {
            [self presentModalViewController:self.overlayViewController.imagePickerController animated:YES];
        } else
        {
             [self.overlayViewController.popoverController presentPopoverFromBarButtonItem:button permittedArrowDirections:UIPopoverArrowDirectionAny animated:YES];
        }
    }
}

- (IBAction)photoLibraryAction:(id)sender
{   
   [self showImagePicker:UIImagePickerControllerSourceTypePhotoLibrary fromButton:sender];
}

- (IBAction)cameraAction:(id)sender
{
   [self showImagePicker:UIImagePickerControllerSourceTypeCamera fromButton:sender];
}

- (IBAction)leftAction:(id)sender
{
    UIImage *img = [self imageRotatedByRadians:[imageView image] :-M_PI/2];
    [imageView setImage: img];
}

- (IBAction)rightAction:(id)sender
{
    UIImage *img = [self imageRotatedByRadians:[imageView image] :M_PI/2];
    [imageView setImage: img];
}


#pragma mark -
#pragma mark Navigation Bar Actions

- (void)recognizeAction:(id)sender
{
   [self.navigationController pushViewController:ketcherViewController animated:YES]; 
    
    UIImage *image = [self.imageView image];
    
    if (self.scrollView.zoomScale > 1.0) {
        NSLog(@"%lf", self.scrollView.zoomScale);
        CGRect rect = CGRectMake(self.scrollView.contentOffset.x / self.scrollView.contentSize.width * image.size.width,
                                 self.scrollView.contentOffset.y / self.scrollView.contentSize.height * image.size.height,
                                 image.size.width / self.scrollView.zoomScale, image.size.height / self.scrollView.zoomScale);
        
        NSLog(@"%lf %lf %lf %lf", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
        CGImageRef imageRef = CGImageCreateWithImageInRect([image CGImage], rect);
        image = [UIImage imageWithCGImage:imageRef]; 
        CGImageRelease(imageRef);
    }
   
   [self.ketcherViewController setupKetcher: image];
}

- (UIView *)viewForZoomingInScrollView:(UIScrollView *)scrollView
{
    return self.imageView;
}

- (void)updateScrollView
{
    UIImage *img = self.imageView.image;
    CGSize areaSize = CGSizeMake(self.view.frame.size.width, self.view.frame.size.height - 44);
    float imgRatio = img.size.width / img.size.height;
    CGRect frame = self.scrollView.frame;
    
    if (areaSize.width / areaSize.height > imgRatio)
    {
        frame.size = CGSizeMake(areaSize.height * imgRatio, areaSize.height);
    } else
    {
        frame.size = CGSizeMake(areaSize.width, areaSize.width / imgRatio);
    }
    
    frame.origin.x = (areaSize.width - frame.size.width) / 2;
    frame.origin.y = (areaSize.height - frame.size.height) / 2;
    
    self.scrollView.frame = frame;
}

#pragma mark -
#pragma mark OverlayViewControllerDelegate

// as a delegate we are being told a picture was taken
- (void)didTakePicture:(UIImage *)picture
{
    if (self.capturedImage == nil)
       self.recognizeButton.enabled = YES;

    [self setCapturedImage:picture];
}

// as a delegate we are told to finished with the camera
- (void)didFinishWithCamera
{
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
    {
        [self dismissModalViewControllerAnimated:YES];
    } else
    {
        [self.overlayViewController.popoverController dismissPopoverAnimated:YES];
    }
    
    if (self.capturedImage != nil)
    {
        UIImage *img = [self prepareImage:capturedImage];
        [self.imageView setImage:img];

        self.scrollView.zoomScale = 1.0;
        [self updateScrollView];
    }
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
   return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    if (self.capturedImage)
        [self updateScrollView];
}

@end