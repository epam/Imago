//
//  KetcherViewController.m
//  ireco
//
//  Created by Boris Karulin on 07.12.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "KetcherViewController.h"


@implementation KetcherViewController

@synthesize webView;

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

- (void)setupKetcher:(NSString *)molfile
{
   /**/
   NSError *error = nil;
   NSString *html = [[NSString alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"ketcher" ofType:@"html"] encoding:NSUTF8StringEncoding error:&error];
   [webView loadHTMLString:html baseURL:[NSURL fileURLWithPath: [[NSBundle mainBundle] bundlePath]]];
   /**/
   //[webView loadRequest:[NSURLRequest requestWithURL: [NSURL fileURLWithPath: [[NSBundle mainBundle] pathForResource:@"ketcher" ofType:@"html"] isDirectory:NO]]];
}

// called when the parent application receives a memory warning
- (void)didReceiveMemoryWarning
{
   // we have been warned that memory is getting low, stop all timers
   //
   [super didReceiveMemoryWarning];
}

@end
