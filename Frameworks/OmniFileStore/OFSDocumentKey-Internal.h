// Copyright 2016-2019 Omni Development, Inc. All rights reserved.
//
// This software may only be used and reproduced according to the
// terms in the file OmniSourceLicense.html, which should be
// distributed with this project and can also be found at
// <http://www.omnigroup.com/developer/sourcecode/sourcelicense/>.

#import <OmniFileStore/OFSDocumentKey.h>

#import <CommonCrypto/CommonCrypto.h>

#define MAX_SYMMETRIC_KEY_BYTES kCCKeySizeAES256
struct skbuf {
    uint16_t len;
    uint8_t bytes[MAX_SYMMETRIC_KEY_BYTES];
};

@interface OFSDocumentKey ()
{
@protected
    /* The contents of our saved blob */
    NSDictionary *passwordDerivation;
    
    /* The decrypted key slots. slots is nil if we are not unlocked/valid. */
    OFSKeySlots *slots;
    
    /* We keep a copy of the wrapping key around so we can re-wrap after a rollover event such as a password change */
    struct skbuf wk;
    
    /* Application label prefix for keychain storage */
    const char *_prefix;
}

// A label uniquely identifying the receiving key based on its PBKDF2 salt. See comments in OFSDocumentKey-KeychainStorageSupport-*.m about where exactly this value is stored (short version: kSecAttrApplicationLabel on iOS and kSecAttrGeneric on Mac, because of radars).
@property (nonatomic, readonly) NSData *applicationLabel;

@end
