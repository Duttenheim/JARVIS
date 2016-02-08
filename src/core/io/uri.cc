//------------------------------------------------------------------------------
/**
    @class JARVIS::Core::URI
 	(C) 2015 See the LICENSE file.
*/
#include "uri.h"
#include "assigns.h"
namespace JARVIS {
namespace Core
{
    
//------------------------------------------------------------------------------
/**
*/
URI::URI()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
URI::URI(const Core::String& path)
{
    this->Resolve(path);
}

//------------------------------------------------------------------------------
/**
*/
URI::URI(const char* path)
{
    this->Resolve(Core::String(path));
}

//------------------------------------------------------------------------------
/**
*/
URI::URI(const URI& rhs)
{
    this->localPath = rhs.localPath;
    this->path = rhs.path;
    this->method = rhs.method;
}

//------------------------------------------------------------------------------
/**
*/
URI::URI(URI&& rhs)
{
    this->localPath = Mv(rhs.localPath);
    this->path = Mv(rhs.path);
    this->method = Mv(rhs.method);
}

//------------------------------------------------------------------------------
/**
*/
URI::~URI()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
URI::Set(const Core::String& path)
{
    this->Resolve(path);
}

//------------------------------------------------------------------------------
/**
*/
const Core::String&
URI::LocalPath() const
{
    return this->localPath;
}

//------------------------------------------------------------------------------
/**
*/
const Core::String&
URI::Path() const
{
    return this->path;
}

//------------------------------------------------------------------------------
/**
*/
void
URI::Resolve(const Core::String& path)
{
    Core::Array<Core::String> tokens = path.Split(":");
    Core::String pathSegment;
    if (tokens.Size() > 0)
    {
        // resolve assigns to pathSegment
        for (const Core::String& str : tokens)
        {
            pathSegment.Append(Assigns::Resolve(str));
        }
    }

    // save method segment
    this->method = pathSegment.ExtractToString("://");
    this->localPath = pathSegment.ExtractToEndFromString(this->method + "://");
    
    this->path = this->method + this->localPath;
}

}} // namespace JARVIS::Core
