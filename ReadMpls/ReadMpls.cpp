/*
    Copyright (C) 2017  HolyWu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "mpls_parse.h"
#include <libbluray/bluray.h>

#include <string>

#include <VapourSynth.h>

static void VS_CC readMplsCreate(const VSMap *in, VSMap *out, void *userData, VSCore *core, const VSAPI *vsapi) {
    const std::string source{ vsapi->propGetData(in, "source", 0, nullptr) };

    mpls_pl * pl = bd_read_mpls(source.c_str());
    if (!pl)
        return vsapi->setError(out, ("ReadMpls: failed to open " + source).c_str());

    vsapi->propSetInt(out, "count", pl->list_count, paReplace);
    for (unsigned i = 0; i < pl->list_count; i++)
        vsapi->propSetData(out, "clip", (source.substr(0, source.find_last_of("/\\") - 8) + "STREAM/" + pl->play_item[i].clip[0].clip_id + ".m2ts").c_str(), -1, paAppend);
    if (pl->list_count == 1)
        vsapi->propSetData(out, "clip", "", -1, paAppend);

    bd_free_mpls(pl);
}

//////////////////////////////////////////
// Init

VS_EXTERNAL_API(void) VapourSynthPluginInit(VSConfigPlugin configFunc, VSRegisterFunction registerFunc, VSPlugin *plugin) {
    configFunc("com.holywu.readmpls", "mpls", "Reads a mpls file and returns a dict", VAPOURSYNTH_API_VERSION, 1, plugin);
    registerFunc("Read", "source:data;", readMplsCreate, nullptr, plugin);
}
