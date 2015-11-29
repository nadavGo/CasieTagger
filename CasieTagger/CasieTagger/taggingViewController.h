//
//  taggingViewController.h
//  CasieTagger
//
//  Created by itiel on 11/26/15.
//  Copyright © 2015 orcam. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "items.h"
#import "taggingTime.h"

@interface taggingViewController : UIViewController

@property (nonatomic) BOOL nowTagging;
@property (weak, nonatomic) taggingTime* currentTaggingTime;
@property (weak, nonatomic) items* currentItem;

- (IBAction)startTaggingButtonPressed:(UIButton *)sender;
- (IBAction)stopTaggingButtonPressed:(UIButton *)sender;
- (IBAction)holdToTagButtonPressed:(UIButton *)sender;

-(void)printTaggingTimeToLog;



@end
