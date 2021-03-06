/*
 Copyright (c) 2015, salesforce.com, inc. All rights reserved.
 
 Redistribution and use of this software in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice, this list of conditions
 and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of
 conditions and the following disclaimer in the documentation and/or other materials provided
 with the distribution.
 * Neither the name of salesforce.com, inc. nor the names of its contributors may be used to
 endorse or promote products derived from this software without specific prior written
 permission of salesforce.com, inc.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import "CSFNetwork.h"
#import "CSFTokenRefresh.h"
#import "CSFNetworkOutputCache.h"

@class CSFAuthRefresh;

@interface CSFNetwork () <NSURLSessionDataDelegate, NSURLSessionDownloadDelegate> {
@protected
    NSNumber *_offlineCacheEnabled;
    NSPointerArray *_outputCachePointers;
}

/**
 Property set to YES when the executer is cancelling execution of actions.
 This prevents new actions from be scheduled.
 */
@property (atomic) BOOL cancelling;

/**
 Property set to YES when the executer is pausing execution of actions.
 This prevents new action from be scheduled.
 */
@property (atomic) BOOL pausing;

@property (nonatomic, strong, readwrite) SFUserAccount *account;
@property (atomic, readwrite, getter=isRefreshingAccessToken) BOOL refreshingAccessToken;

@property (nonatomic, strong) NSOperationQueue *queue;
@property (nonatomic, readwrite, strong) NSURLSession *ephemeralSession;
@property (nonatomic, copy) NSString *userAgent;
@property (nonatomic, assign, readwrite) NSUInteger actionCount;
@property (nonatomic, strong, readonly) NSPointerArray *outputCachePointers;
@property (nonatomic, assign, getter=hasCacheBeenConfigured) BOOL cacheIsConfigured;

- (id)initWithUserAccount:(SFUserAccount*)account;

/**
 Resets any data associated with the session
 */
- (void)resetSession;

- (CSFAction*)duplicateActionInFlight:(CSFAction*)action;

/*!
 Provides a means for low-level code to tell us that this device has been de-authorized.
 This can happen if the device is unchecked from Chatter settings in the org setup.
 */
- (void)receivedDevicedUnauthorizedError:(CSFAction*)action;

- (CSFAction*)actionForSessionTask:(NSURLSessionTask*)task;

/**
 Provides a mean for test code to check shared instances of CSFNetwork
 */
+ (instancetype)cachedNetworkForUserAccount:(SFUserAccount*)account;

@end
