//
//  KetcherViewController.m
//  ireco
//
//  Created by Boris Karulin on 07.12.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "KetcherViewController.h"

@implementation KetcherViewController

@synthesize webView, activityView, molfile, prevImage, recognizer, recognizerThread;

#pragma mark -
#pragma mark KetcherViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
   if (self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])
   {
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

   [super dealloc];
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
   
   if (self.molfile != nil)
   {
      NSString *jsLoadMol = [NSString stringWithFormat: @"ketcher.setMolecule('%@');", [self.molfile stringByReplacingOccurrencesOfString:@"\n" withString:@"\\n"]];
      [self.webView performSelectorOnMainThread:@selector(stringByEvaluatingJavaScriptFromString:) withObject: jsLoadMol waitUntilDone: YES];
   } else {
      [webView loadHTMLString:@"<html><head></head><body>An error occured.</body></html>" baseURL:nil];
   }
   
   [self.activityView stopAnimating];
   [pool drain];
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
}

// called when the parent application receives a memory warning
- (void)didReceiveMemoryWarning
{
   // we have been warned that memory is getting low, stop all timers
   //
   [super didReceiveMemoryWarning];
}

@end
