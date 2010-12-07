//
//  KetcherViewController.m
//  ireco
//
//  Created by Boris Karulin on 07.12.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "KetcherViewController.h"
#import "Recognizer.h"

@implementation KetcherViewController

@synthesize webView, activityView, molfile, prevImage;

#pragma mark -
#pragma mark KetcherViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
   self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
   return self;
}

- (void)viewDidUnload
{
}

- (void)dealloc
{	
   [super dealloc];
}

- (void)setupKetcher:(UIImage *)image
{
   [self.activityView startAnimating];
   
   NSThread* recognizerThread = [[NSThread alloc] initWithTarget:self
                                                        selector:@selector(recognizingProc:)
                                                          object:image];
   [recognizerThread start];
   
   /**/
   //[webView loadRequest:[NSURLRequest requestWithURL: [NSURL fileURLWithPath: [[NSBundle mainBundle] pathForResource:@"ketcher" ofType:@"html"] isDirectory:NO]]];
   
   //[webView stringByEvaluatingJavaScriptFromString:@"alert('ok!');"];
}

- (void)recognizingProc:(UIImage *)image
{
   if (prevImage == nil || prevImage != image)
   {
      Recognizer *recognizer = [Recognizer recognizerWithImage:image];
      
      self.molfile = [recognizer recognize];
   }

   self.prevImage = image;
   
   if (self.molfile != nil)
   {
      NSLog(self.molfile);
      
      NSError *error = nil;
      NSString *html = [[NSString alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"ketcher" ofType:@"html"] encoding:NSUTF8StringEncoding error:&error];
      html = [html stringByReplacingOccurrencesOfString:@"MOLFILE_PLACEHOLDER" withString:self.molfile];
      [webView loadHTMLString:html baseURL:[NSURL fileURLWithPath: [[NSBundle mainBundle] bundlePath]]];
   } else {
      [webView loadHTMLString:@"<html><head></head><body>An error occured.</body></html>" baseURL:nil];
   }
   
   [self.activityView stopAnimating];
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
   /*
   if (self.molfile != nil)
   {
      if ([self.webView stringByEvaluatingJavaScriptFromString:@"ui.initialized"] == @"true")
      {
         NSString *jsLoadMol = @"ketcher.setMolecule('MOLFILE_PLACEHOLDER');";
         [self.webView stringByEvaluatingJavaScriptFromString:[jsLoadMol stringByReplacingOccurrencesOfString:@"MOLFILE_PLACEHOLDER" withString:self.molfile]];
      }
   }
    */
}

// called when the parent application receives a memory warning
- (void)didReceiveMemoryWarning
{
   // we have been warned that memory is getting low, stop all timers
   //
   [super didReceiveMemoryWarning];
}

@end
