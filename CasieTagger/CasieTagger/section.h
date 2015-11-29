//
//  section.h
//  CasieTagger
//
//  Created by orcam on 11/26/15.
//  Copyright © 2015 orcam. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "item.h"


@interface section : NSObject

@property NSString* name;

@property NSMutableArray* items;


-(void)addItemToSection:(item*)item;
@end
