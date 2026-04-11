/*
 * ModSharp
 * Copyright (C) 2023-2026 Kxnrl. All Rights Reserved.
 *
 * This file is part of ModSharp.
 * ModSharp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * ModSharp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with ModSharp. If not, see <https://www.gnu.org/licenses/>.
 */

#include "cstrike/interface/IGameSystem.h"
#include "module.h"

#include <cstring>

static bool IsComparableGameSystemName(const char* name)
{
    if (name == nullptr || !CAddress(name).IsValid() || name[0] == '\0')
        return false;

    for (std::size_t i = 0; i < 256; ++i)
    {
        if (name[i] == '\0')
            return true;
    }

    return false;
}

CBaseGameSystemFactory* GetGameSystemFactory()
{
    return CBaseGameSystemFactory::GetFirst();
}

void* FindGameSystemByName(const char* name)
{
    auto list = CBaseGameSystemFactory::GetFirst();

    while (list)
    {
        if (IsComparableGameSystemName(list->m_pszName) && strcmp(list->m_pszName, name) == 0)
        {
            return list->m_pInstance;
        }

        list = list->m_pNext;
    }

    return nullptr;
}
