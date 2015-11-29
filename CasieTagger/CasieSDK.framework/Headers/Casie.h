//
//  Casie.h
//  CasieSDK
//
//  Created by Quickode on 10/19/15.
//  Copyright © 2015 Quickode. All rights reserved.
//
/*
 To make bluetooth work add:
 <key>UIBackgroundModes</key>
	<array><string>bluetooth-central</string></array>
 to your apps info.plist
 
 */


#import <Foundation/Foundation.h>
#import "CasieFace.h"
#import "CasiePerson.h"

@import UIKit;



typedef enum DeviceState{
    DeviceState_disconnected,
    DeviceState_detected,
    DeviceState_connecting,
    DeviceState_connected,
    DeviceState_sendingData
} DeviceState;

typedef enum WifiState{
    WifiState_NotReachable,
    WifiState_ReachableViaWiFi,
    WifiState_ReachableViaWWAN,
    WifiState_RequestFailed //in case some thing went wrong
} WifiState;

typedef enum ChargerState{
    ChargerState_Disconnected,
    ChargerState_Connected,
    ChargerState_Error
} ChargerState;



@protocol CasieDelegate <NSObject>
@optional
/**
 This delegate is invoked when the CASIE device connection state was changed.
 @param state The current Device state.
 **/
-(void) CASIEConnectionStateUpdated:(DeviceState)state;
-(void) FaceDetected:(CasieFace*)face atTimestamp:(NSDate*)time;
-(void) QRCodeDetected:(NSArray*)code atTimestamp:(NSDate*)time; //Not implemented
-(void) barcodeDetected:(NSArray*)code atTimestamp:(NSDate*)time; //Not implemented

/**
 This delegate is invoked when a new set of words is sent from the device.
 @param arrWords An Array that contains arrays of words and it's probability.
 example: [[probability(NSNumber),word(NSString)], [probability,word],...]
 @param time The time that the words were sent from the device
 **/
-(void) wordsRecieved:(NSArray*)arrWords atTime:(NSDate*)time;
/**
 This delegate is invoked when a new periperal is detected.
 @param peripheralData A Dictionary that contains the keys: ID, Name and RSSI.
 **/
-(void)scanningAndFoundNewPeripheral:(NSDictionary*)peripheralData;

-(void)ChargerStateUpdated:(ChargerState)chargerState;

-(void)printTextToConsole:(NSString*)txt;
@end

@interface Casie : NSObject 

@property (nonatomic, weak) id <CasieDelegate> delegate;

+ (instancetype)sharedInstance;

#pragma mark - communication

/**
 Connects your phone to the device
 **/
-(void) connect;
/**
 Disconnects your phone from the device
 **/
-(void)disconnect;
/**
 Get the current devices state
 **/
-(DeviceState) state; //(disconnected, detected, connecting, connected, sendingData)
-(void) getBatteryPercentageWithBlock:(void (^)(UInt8 batteryLevel)) batteryBlock;

-(void) getChargerStateWithBlock:(void (^)(ChargerState chargerState)) chargerBlock;

-(void) scanToFindPeripherals;
-(void) stopScanForPeripherals;

-(void)pairPeripheralId:(NSString*)peripheralId;
-(BOOL)removePeripheralId;
-(NSString*)getPairedPeripheralId;

/**
 This block requests the image from the device that is associated to this face. If face arrived it will be added automatically to the face in the DB
 @param face The face that you want it's image
 @return image and error - one of them will always be nil
 **/
-(void) requestImageForFace:(CasieFace*)face  WithBlock:(void (^)(UIImage *image, NSError *error)) block;
//-(NSArray*) requestCASIEMotionsForTime:(NSDate*)time1 toTime:(NSDate*)time2;

#pragma mark - Firmware update

-(void)getCurrentHardwareVersionWithBlock:(void(^)(NSString* version))version;
-(void)getCurrentSoftwareVersionWithBlock:(void(^)(NSString* version))version;

/*not implemented
-(NSDictionary*) getWifiData;
-(void) setWifiPassword:(NSString*)password forNetwork:(WifiNetwork*)network;
-(WifiState) getWifiState;
-(BOOL) upgradeFirmware;
*/
#pragma mark - Person/ Faces methods
/**
 Returns an array with all the people that exist in the DB
 @return Array with all the people
 **/
-(NSArray*) getAllPeople;
/**
 Creates a new person and adds him to the DB
 @return copy of the person with the new personID
 **/
-(CasiePerson*) createNewPerson;
/**
 Removes the person from the DB, all of the person faces will be deleted as well
 @return YES if delete succeeded, NO if not
 **/
-(BOOL) removePersonByPersonID:(NSString*)personID;

-(NSArray*) getAllFacesOfPersonByPersonID:(NSString*)personID;
/**
 Adds a face to the specified person
 @param face casieFace that was received from calling the method: "-(CasieFace*) generateFaceFromImage:(UIImage*)image"
 @param person The person you want to add the face to
 @return YES if face was added to person
 **/
-(BOOL) associateFace:(CasieFace*)face ToPerson:(CasiePerson*)person;
/**
 Removes the face from the DB and.
 @return YES if delete succeeded, NO if not
 **/
-(BOOL)deleteFaceWithFaceId:(NSString*)faceId;

-(BOOL)removeFaceWithFaceId:(NSString*)faceId fromPersonWithPersonID:(NSString*)personId;
/**
 Returns the person that has the best match to the specified face
 @param face The CasieFace that will be used to find the best match
 @return The best matched CasiePerson, returns nil if no such person exists
 **/
-(CasiePerson*) bestPersonMatchForFace:(CasieFace*)face; //(return nil if no person exists)
/**
 Calculates the matching score for all people in the DB to the given Face. (lower score means better match).
 @param face The face you want to detect possible matches.
 @param underScore people that there score is lower than this parameter will not be sent back.
 @return A dictionary that contains the Person ID as key and score as value.
 **/
-(NSDictionary*) detectPossibleMatchesFrom:(CasieFace*)face underScore:(double)underScore;

-(double) similarityOf:(CasieFace*)face1 and:(CasieFace*)face2;

-(CasieFace*) generateFaceFromImage:(UIImage*)image; //calling REST server api


-(void)quickConnectionToDeviceWithBestSignal;

#pragma mark - other methods
-(NSArray*) getAllFacesFromTime:(NSDate*)from toTime:(NSDate*)to;
-(NSArray*) getAllDeviceFaces;
-(NSArray*) getAllAppFaces;
-(NSArray*) getAllFaces;




#pragma mark - debug methods

-(void)mockImageReceivedFromDeviceWithImage:(UIImage*)image andVector:(NSArray*)arrVector;
-(CasieFace*) generateDeviceFaceFromImage:(UIImage*)image andFeatures:(NSArray*)arrFeatures;

@end
