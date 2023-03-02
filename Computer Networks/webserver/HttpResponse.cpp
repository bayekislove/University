#include <string>
#include <sstream>
#include <fstream>
#include <map>

static std::map<std::string, std::string> extensions = {
    {"txt", "text/plain;charset=utf-8"},
    {"html", "text/html;charset=utf-8"},
    {"css", "text/css;charset=utf-8"},
    {"jpg", "image/jpeg"},
    {"jpeg", "image/jpeg"},
    {"png", "image/png"},
    {"pdf", "application/pdf"},
};

std::string static inline getFileType(std::string path)
{
    std::string extension = path.substr(path.find_last_of(".") + 1, path.length() - 1);
    if(extensions.find(extension) != extensions.end())
    {
        return extensions[extension];
    }
    return "application/octet-stream";
}

std::string inline MovedPermanentlyResponse()
{
    return "HTTP/1.1 301 Moved Permanently\nLocation: /index.html\r\n\0";
}

std::string inline OkResponse(std::string path)
{
    std::ifstream t(path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string resp = buffer.str();
    return "HTTP/1.1 200 OK\nContent-Type: " + getFileType(path) + "\nContent-Length: " + 
            std::to_string(resp.length()) + "\n\n" + resp + "\0";
}

std:: string inline ForbiddenReponse()
{
    return "HTTP/1.1 403 Forbidden\n304 Trying to get access to another's domain files\n\0";;
}

std:: string inline NotFoundReponse()
{
    return "HTTP/1.1 404 Not Found\n\n404 File Not Found\n\0";
}

std:: string inline NotImplementedReponse()
{
    return "HTTP/1.1 501 Not Implemented\n501 Not Implemented\n\0";
}
