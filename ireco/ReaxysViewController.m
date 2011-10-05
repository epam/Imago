//
//  ReaxysViewController.m
//  ireco
//
//  Created by Karulin Boris on 03.10.11.
//  Copyright 2011 Scite. All rights reserved.
//

#import "ReaxysViewController.h"

@implementation ReaxysViewController

@synthesize webView, activityView, smiles;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return YES;
}

- (void) viewDidAppear:(BOOL)animated
{
   [webView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:@"about:blank"]]];
   
   //NSString *urlString = @"https://www.reaxys.com/reaxys/secured/hopinto.do?context=S&query=SMILES%3D'CC'&qname=2-Hydroxymethylen-dihydrotestololactones&options=product&ln=";

   if (self.smiles != nil && self.smiles != @"") {
      NSString *urlString = @"https://www.reaxys.com/reaxys/secured/hopinto.do?context=S";
      urlString = [urlString stringByAppendingString:[[@"&query=SMILES%3D'" stringByAppendingString:self.smiles] stringByAppendingString:@"'"]];
      urlString = [urlString stringByAppendingString:@"&qname=2-Hydroxymethylen-dihydrotestololactones"];
      urlString = [urlString stringByAppendingString:@"&ln="];
      [webView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlString]]];
   }
}
@end
