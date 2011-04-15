//
//  Recognizer.h
//  ireco
//
//  Created by Boris Karulin on 07.12.10.
//  Copyright 2010 Scite. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface Recognizer : NSObject
{
@private
   qword sessionId;
   imago::ChemicalStructureRecognizer *csr;
   
}

- (NSString *)recognize: (UIImage *)image;

@end
