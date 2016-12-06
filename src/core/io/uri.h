#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::URI
	
    A URI is a type of string which is automatically resolved using the
    assign registry to retrieve relative paths.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "util/string.h"
namespace JARVIS {
namespace Core
{
class URI
{
public:

    /// constructor
    URI();
    /// constructor from string
    URI(const Core::String& path);
    /// construct from const char* for convenience
    URI(const char* path);
    /// copy URIs
    URI(const URI& rhs);
    /// move constructor from other URI
    URI(URI&& rhs);
    /// destructor
    virtual ~URI();
    
    /// set URI path
    void Set(const Core::String& path);
    
    /// get local path
    const Core::String& LocalPath() const;
    /// get full path
    const Core::String& Path() const;
    
private:
    /// helper function to split strings into fragments
    void Resolve(const Core::String& path);
    
    Core::String localPath;
    Core::String path;

    Core::String method;
};

}} // namespace JARVIS::Core