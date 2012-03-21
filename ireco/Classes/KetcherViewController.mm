//
//  KetcherViewController.m
//  ireco
//
//  Created by Boris Karulin on 07.12.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "indigo.h"
#import "KetcherViewController.h"
#import "MagnifierView.h"

@implementation KetcherViewController

@synthesize webView, activityView, molfile, prevImage, recognizer, recognizerThread, touchTimer, navigationItem, reaxysViewController, mailComposerController, lastTouch;

#pragma mark -
#pragma mark KetcherViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
   if (self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])
   {
       // just create one loop and re-use it.
       loupe = [[MagnifierView alloc] init];
       loupe.viewToMagnify = self.view;

      self.recognizerThread = [[[NSThread alloc] initWithTarget:self selector:@selector(recognizerThreadProc) object:nil] autorelease];
      [self.recognizerThread start];
   }
   return self;
}

- (void)viewDidLoad
{
    UIBarButtonItem *mailButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemCompose target:self action:@selector(sendMail:)];
    NSArray *rightButtons = [[NSArray alloc] initWithObjects: self.navigationItem.rightBarButtonItem, mailButton, nil];
    
    [self.navigationItem setRightBarButtonItems:rightButtons];
    
    [mailButton release];
    [rightButtons release];
    
   ReaxysViewController *reaxys = [[ReaxysViewController alloc] initWithNibName:@"ReaxysViewController" bundle:nil];
   self.reaxysViewController = reaxys;
   [reaxys release];
    
    [(MainWindow *)[[[UIApplication sharedApplication] delegate] window] startObserveView:self.webView andDelegate:self];
    
   NSError *error = nil;
   NSString *html = [[NSString alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"ketcher" ofType:@"html"] encoding:NSUTF8StringEncoding error:&error];
   [webView loadHTMLString:html baseURL:[NSURL fileURLWithPath: [[NSBundle mainBundle] bundlePath]]];
   [html release];
}

- (void)viewWillAppear:(BOOL)animated
{
    self.reaxysViewController.smiles = [self saveSmilesFromKetcher];
    
    self.navigationItem.rightBarButtonItem.enabled = (self.reaxysViewController.smiles != nil && self.reaxysViewController.smiles != @"");
}

- (void)viewDidUnload
{
}

- (void)dealloc
{	
   
   [webView release];
   [activityView release];
    
   [mailComposerController release];
   [reaxysViewController release];
   
   keepAlive = NO;
   
   while ([recognizerThread isExecuting])
   {
      // wait thread finished
   }
   
   [recognizerThread release];
   
   if (self.molfile != nil)
      [self.molfile release];
    
    [loupe release];
    loupe = nil;
    
    [lastTouch release];

   [super dealloc];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
   return YES;
}

- (void)setupKetcher:(UIImage *)image
{
   [self.activityView startAnimating];
   
   [self performSelector:@selector(recognizingProc:) onThread:self.recognizerThread withObject:image waitUntilDone:NO];
}

- (void)recognizerThreadProc
{
   NSAutoreleasePool *initPool = [[NSAutoreleasePool alloc] init];
   
   self.recognizer = [[[Recognizer alloc] init] autorelease];

   [initPool drain];
   
   NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
   NSRunLoop *runLoop = [NSRunLoop currentRunLoop];
   
   keepAlive = YES;
   [[NSRunLoop currentRunLoop] addPort:[NSMachPort port] forMode:NSDefaultRunLoopMode];
   
   while (keepAlive && [runLoop runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]])
   {
      // run loop spinned ones
   }

   self.recognizer = nil;

   [pool drain];
}

- (void)recognizingProc:(UIImage *)image
{
   NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
   if (prevImage == nil || prevImage != image)
   {
      [self setMolfile:[recognizer recognize: image]];
   }

   self.prevImage = image;
   
   [self loadMolfileToKetcher];
   
   [self.activityView stopAnimating];
   [pool drain];
}

- (void)loadMolfileToKetcher
{
    NSString *molfile_or_empty = self.molfile;
    if (self.molfile == nil)
       molfile_or_empty = @"";
   
    NSString *jsLoadMol = [NSString stringWithFormat: @"ketcher.setMolecule('%@');", [molfile_or_empty stringByReplacingOccurrencesOfString:@"\n" withString:@"\\n"]];
    [self.webView performSelectorOnMainThread:@selector(stringByEvaluatingJavaScriptFromString:) withObject: jsLoadMol waitUntilDone: YES];
   
   if (self.molfile == nil) {
        // Show a message box here to create a feedback
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Exception" message:@"Cannot recognize. Would you like to send a report?" delegate:self cancelButtonTitle:@"No" otherButtonTitles:@"Yes", nil];
        [alert show];
        [alert release];
    }
}

- (void)alertView:(UIAlertView *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
   // the user clicked one of the OK/Cancel buttons
   if (buttonIndex == 1)
   {
      [self sendMail: self];
   }
}

- (NSString *)saveSmilesFromKetcher
{
   return [self.webView stringByEvaluatingJavaScriptFromString:@"ketcher.getSmiles();"];
}

- (NSString *)saveMolfileFromKetcher
{
    return [self.webView stringByEvaluatingJavaScriptFromString:@"ketcher.getMolfile();"];
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
}

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    NSString *url = [request.URL absoluteString];
    NSArray *urlArray = [url componentsSeparatedByString:@"?"];
    
    if (urlArray.count > 1)
    {
        NSString *paramsString = [urlArray objectAtIndex:1];
        NSArray *urlParamsArray = [paramsString componentsSeparatedByString:@"&"];
        NSString *cmd = [[[urlParamsArray objectAtIndex:0] componentsSeparatedByString:@"="] objectAtIndex:1];
        
        if ([cmd isEqualToString:@"log"] && urlParamsArray.count > 1)
        {
            NSLog(@"%@", [[[[urlParamsArray objectAtIndex:1] componentsSeparatedByString:@"="] objectAtIndex:1] stringByReplacingPercentEscapesUsingEncoding:NSASCIIStringEncoding]);
            
            return NO;
        }

        if ([cmd isEqualToString:@"layout"] && urlParamsArray.count > 1)
        {
            const char *layoutMolfile = [[[[[urlParamsArray objectAtIndex:1] componentsSeparatedByString:@"="] objectAtIndex:1] stringByReplacingPercentEscapesUsingEncoding:NSASCIIStringEncoding] cStringUsingEncoding:NSASCIIStringEncoding];
            
            int mol = indigoLoadMoleculeFromString(layoutMolfile);
            
            if (mol == -1)
            {
                NSLog(@"%s\n", indigoGetLastError());
                return NO;
            }
            
            indigoLayout(mol);
            
            layoutMolfile = indigoMolfile(mol);
            
            self.molfile = [NSString stringWithCString:layoutMolfile encoding:NSASCIIStringEncoding];
            
            indigoFree(mol);
            
            [self loadMolfileToKetcher];
            
            return NO;
        }

        if ([cmd isEqualToString:@"loupe"] && urlParamsArray.count > 1)
        {
            NSString *show = [[[[urlParamsArray objectAtIndex:1] componentsSeparatedByString:@"="] objectAtIndex:1] lowercaseString];
            
            if ([show isEqualToString:@"true"])
            {
                self.touchTimer = [NSTimer scheduledTimerWithTimeInterval:0.5
                                                                   target:self
                                                                 selector:@selector(showLoupe)
                                                                 userInfo:nil
                                                                  repeats:NO];
                loupe.touchPoint = [self.lastTouch locationInView:self.view];
                [loupe setNeedsDisplay];
            } else
            {
                [loupe removeFromSuperview];
            }
            
            return NO;
        }
    }
        
    return YES; 
}

- (IBAction)sendMail:(id)sender
{
    NSString *moldata = [self saveMolfileFromKetcher];
    
    MFMailComposeViewController *mailController = [[MFMailComposeViewController alloc] init];
    self.mailComposerController = mailController;
    [mailController release];
    
    if ([MFMailComposeViewController canSendMail])
    {
        self.mailComposerController.mailComposeDelegate = self;
        
        NSDateFormatter *formatter;
        NSString        *dateString;
       
        formatter = [[NSDateFormatter alloc] init];
        [formatter setDateFormat:@"dd-MM-yyyy HH:mm"];
       
        dateString = [formatter stringFromDate:[NSDate date]];
       
        [formatter release];
       
        [self.mailComposerController setSubject:@"BeerMat molecule and photo"];
       
        [self.mailComposerController 
            addAttachmentData:[moldata dataUsingEncoding:[NSString defaultCStringEncoding]] 
            mimeType:@"text/plain"
            fileName:[NSString stringWithFormat: @"edited %@.mol", dateString]];
        if (self.molfile != nil)
        {
           [self.mailComposerController 
            addAttachmentData:[self.molfile dataUsingEncoding:[NSString defaultCStringEncoding]] 
            mimeType:@"text/plain"
            fileName:[NSString stringWithFormat: @"original %@.mol", dateString]];
        }

        if (prevImage != 0)
        {
            NSLog(@"Converting image into Jpeg...\n");
            NSData *rawImage = UIImageJPEGRepresentation(prevImage, 1.0f);
            [self.mailComposerController
               addAttachmentData:rawImage
               mimeType:@"image/jpeg"
               fileName:[NSString stringWithFormat: @"photo %@.jpg", dateString]];
            NSLog(@"Converting image into Png...\n");
            NSData *rawImagePng = UIImagePNGRepresentation(prevImage);
            [self.mailComposerController
             addAttachmentData:rawImagePng
             mimeType:@"image/png"
             fileName:[NSString stringWithFormat: @"photo %@.png", dateString]];
        }
        [self presentModalViewController:self.mailComposerController animated:YES];
    }
}

- (IBAction)findInReaxys:(id)sender
{
    NSString *smiles = [self saveSmilesFromKetcher];
    
    if (smiles != nil && smiles != @"") {
        self.reaxysViewController.smiles = smiles;
        
        [self.navigationController pushViewController:self.reaxysViewController animated:YES];
    }
}

- (void)mailComposeController:(MFMailComposeViewController*)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError*)error
{
    [self dismissModalViewControllerAnimated:YES];
}

- (void)userDidTouchStart:(UITouch *)touch {
    self.lastTouch = touch;
}
- (void)userDidTouchMove:(UITouch *)touch {
	loupe.touchPoint = [touch locationInView:self.view];
	[loupe setNeedsDisplay];
}
- (void)userDidTouchEnd {
	[self.touchTimer invalidate];
	self.touchTimer = nil;
	[loupe removeFromSuperview];
}
- (void)showLoupe
{
    [self.view.superview addSubview:loupe];
}

// called when the parent application receives a memory warning
- (void)didReceiveMemoryWarning
{
   // we have been warned that memory is getting low, stop all timers
   //
   [super didReceiveMemoryWarning];
}

@end
