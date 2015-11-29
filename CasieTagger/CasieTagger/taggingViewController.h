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

@interface taggingViewController : UIViewController <UITableViewDelegate, UITableViewDataSource>


@property (nonatomic) BOOL nowTagging;
@property (weak, nonatomic) taggingTime* currentTaggingTime;
@property (weak, nonatomic) items* currentItem;
@property (weak, nonatomic) NSArray* timesTableViewDataSource;

- (IBAction)startTaggingButtonPressed:(UIButton *)sender;
- (IBAction)stopTaggingButtonPressed:(UIButton *)sender;

-(void)printTaggingTimeToLog;
-(NSString*)description;


@end
