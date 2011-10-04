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

@synthesize webView, activityView, findInReaxysButton, molfile, prevImage, recognizer, recognizerThread, touchTimer;

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
   NSError *error = nil;
   NSString *html = [[NSString alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"ketcher" ofType:@"html"] encoding:NSUTF8StringEncoding error:&error];
   [webView loadHTMLString:html baseURL:[NSURL fileURLWithPath: [[NSBundle mainBundle] bundlePath]]];
   [html release];
}

- (void)viewDidUnload
{
}

- (void)dealloc
{	
   
   [webView release];
   [activityView release];
   
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
    if (self.molfile != nil)
    {
        NSString *jsLoadMol = [NSString stringWithFormat: @"ketcher.setMolecule('%@');", [self.molfile stringByReplacingOccurrencesOfString:@"\n" withString:@"\\n"]];
        [self.webView performSelectorOnMainThread:@selector(stringByEvaluatingJavaScriptFromString:) withObject: jsLoadMol waitUntilDone: YES];
    } else {
        [webView loadHTMLString:@"<html><head></head><body>An error occured.</body></html>" baseURL:nil];
    }
}

- (NSString *)saveSmilesFromKetcher
{
   return [self.webView stringByEvaluatingJavaScriptFromString:@"ketcher.getSmiles();"];
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
                [self.view.superview addSubview:loupe];
            } else
            {
                [loupe removeFromSuperview];
            }
            
            return NO;
        }
    }
        
    return YES; 
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    NSLog(@"touchstart");
    if (touches.count != 1)
        return;
	self.touchTimer = [NSTimer scheduledTimerWithTimeInterval:0.5
                                                       target:self
                                                     selector:@selector(showLoupe)
                                                     userInfo:nil
                                                      repeats:NO];
	UITouch *touch = [touches anyObject];
	loupe.touchPoint = [touch locationInView:self.view];
	[loupe setNeedsDisplay];
}
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
	UITouch *touch = [touches anyObject];
	loupe.touchPoint = [touch locationInView:self.view];
	[loupe setNeedsDisplay];
}
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    if (touches.count != 0)
        return;
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
