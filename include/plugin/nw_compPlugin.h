/*
 *                         OpenSplice DDS
 *
 *   This software and documentation are Copyright 2006 to 2017 PrismTech
 *   Limited, its affiliated companies and licensors. All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#ifndef NW_COMPPLUGIN_H
#define NW_COMPPLUGIN_H

typedef unsigned long (*nw_cp_maxfn)(unsigned long);
typedef unsigned long (*nw_cp_compfn)(void *, unsigned long, const void *, unsigned long, void *);
typedef unsigned long (*nw_cp_uncompfn)(void *, unsigned long, const void *, unsigned long);
typedef void (*nw_cp_exitfn)(void *);

typedef struct
{
   nw_cp_maxfn maxfn;
   nw_cp_compfn compfn;
   nw_cp_uncompfn uncompfn;
   nw_cp_exitfn exitfn;
   void *parameter;
} nw_compressor;

typedef void (*nw_cp_initfn)(nw_compressor *, const char *);

#endif /* NW_COMPPLUGIN_H */

