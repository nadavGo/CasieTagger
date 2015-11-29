//
//  taggingViewController.m
//  CasieTagger
//
//  Created by itiel on 11/26/15.
//  Copyright © 2015 orcam. All rights reserved.
//

#import "taggingViewController.h"


@implementation taggingViewController

- (IBAction)startTaggingButtonPressed:(UIButton *)sender {
	
	//if already tagging, skip
	if (_nowTagging == YES)
	{
		return;
	}

	[self setNowTagging:YES];

	//add new tagging time to the item
	taggingTime* newTagging = [taggingTime new];
	[newTagging setStart:[NSDate date]];
	[_currentItem.taggingTimes addObject:newTagging];
	
	[self setCurrentTaggingTime:newTagging];
}

- (IBAction)stopTaggingButtonPressed:(UIButton *)sender {
	
	// if already not tagging, skip
	if (_nowTagging == NO)
	{
		return;
	}
	
	// set now as stop tagging time
	[_currentTaggingTime setStop:[NSDate date]];

	[self setNowTagging:NO];
	
	[self printTaggingTimeToLog];
}

- (IBAction)holdToTagButtonPressed:(UIButton *)sender {
}

-(void)printTaggingTimeToLog
{
	NSLog(@"tagging for item: %@ from: %@ to %@", _currentItem, _currentTaggingTime.start, _currentTaggingTime.stop);
}

@end
