//
//  TagsTableViewController.h
//  CasieTagger
//
//  Created by orcam on 11/26/15.
//  Copyright © 2015 orcam. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "section.h"
#import "item.h"

@interface TagsTableViewController : UITableViewController

@property NSMutableArray* sections;


- (IBAction)addItemBtn:(UIBarButtonItem *)sender;

- (IBAction)addSectionBtn:(UIBarButtonItem *)sender;
    

@end
