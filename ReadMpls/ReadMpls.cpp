/*
    Copyright (C) 2017-2021  HolyWu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <string>

#include <VapourSynth.h>
#include <VSHelper.h>

#include <libbluray/bluray.h>

using namespace std::literals;

static void VS_CC readMplsCreate(const VSMap* in, VSMap* out, [[maybe_unused]] void* userData, [[maybe_unused]] VSCore* core, const VSAPI* vsapi) {
    auto err{ 0 };

    auto bd_path{ vsapi->propGetData(in, "bd_path", 0, nullptr) };
    auto playlist{ int64ToIntS(vsapi->propGetInt(in, "playlist", 0, nullptr)) };
    auto angle{ int64ToIntS(vsapi->propGetInt(in, "angle", 0, &err)) };

    auto bd{ bd_open(bd_path, nullptr) };
    if (!bd)
        return vsapi->setError(out, ("ReadMpls: failed to open "s + bd_path).c_str());

    auto titleInfo{ bd_get_playlist_info(bd, playlist, angle) };
    if (!titleInfo) {
        vsapi->setError(out, "ReadMpls: failed to get information of the specified playlist or angle");
        bd_close(bd);
        return;
    }

    vsapi->propSetInt(out, "count", titleInfo->clip_count, paReplace);
    for (auto i{ 0U }; i < titleInfo->clip_count; i++) {
        auto filename{ titleInfo->clips[i].clip_id + ".m2ts"s };
        vsapi->propSetData(out, "clip", (bd_path + "/BDMV/STREAM/"s + filename).c_str(), -1, paAppend);
        vsapi->propSetData(out, "filename", filename.c_str(), -1, paAppend);
    }
    if (titleInfo->clip_count == 1) {
        vsapi->propSetData(out, "clip", "", -1, paAppend);
        vsapi->propSetData(out, "filename", "", -1, paAppend);
    }

    bd_free_title_info(titleInfo);
    bd_close(bd);
}

//////////////////////////////////////////
// Init

VS_EXTERNAL_API(void) VapourSynthPluginInit(VSConfigPlugin configFunc, VSRegisterFunction registerFunc, VSPlugin* plugin) {
    configFunc("com.holywu.readmpls", "mpls", "Get m2ts clip id from a playlist and return a dict", VAPOURSYNTH_API_VERSION, 1, plugin);
    registerFunc("Read",
                 "bd_path:data;"
                 "playlist:int;"
                 "angle:int:opt;",
                 readMplsCreate, nullptr, plugin);
}
