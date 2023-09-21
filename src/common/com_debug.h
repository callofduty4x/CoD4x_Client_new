#include "../win32/win_debugcon.h"
#include <fmt/format.h>
#include <fstream>


class ComDebugConsole : public DebugConsole
{
public:
    ComDebugConsole(HINSTANCE hInstance, const char* title) : DebugConsole(hInstance, title), m_logfile("debug_out.log"){}
	  ComDebugConsole(HINSTANCE hInstance, const char* title, int initialwidth, int initialheigth) : DebugConsole(hInstance, title, initialwidth, initialheigth), m_logfile("debug_out.log"){}
    
    template <typename... T> void Print(fmt::format_string<T...> fmt, T&&... args)
    {
        try {
            const std::string msg = fmt::format(fmt, std::forward<T>(args)...);
            this->PrintInternal(msg.c_str());
            m_logfile << msg;
        } catch (const std::exception& e) {
            fprintf(stderr, "Error in the format: %s\n", e.what());
        }
    }

private:
    std::ofstream m_logfile;

};


extern ComDebugConsole *dbgCon;


/* Example for fmt

template<> struct fmt::formatter<GfxDrawSurfListInfo>
{
  template<typename ParseContext> constexpr auto parse(ParseContext& ctx);

  template<typename FormatContext> auto format(GfxDrawSurfListInfo const& type, FormatContext& ctx);
};

template<typename ParseContext> constexpr auto fmt::formatter<GfxDrawSurfListInfo>::parse(ParseContext& ctx)
{
  return ctx.begin();
}

template<typename FormatContext> auto fmt::formatter<GfxDrawSurfListInfo>::format(GfxDrawSurfListInfo const& type, FormatContext& ctx)
{
  return fmt::format_to(ctx.out(), "drawSurfCount: {0} BaseTechType: {1} LightMaterial: {2} CameraView: {3} ViewOrigin: {4} {5} {6} {7}", type.drawSurfCount, type.baseTechType, (type.light && type.light->def) ? type.light->def->name : "NULL", type.cameraView, type.viewOrigin[0], type.viewOrigin[1], type.viewOrigin[2], type.viewOrigin[3]);
}


*/