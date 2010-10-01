/*
 * Copyright (c) 1996-2009 Barton P. Miller
 * 
 * We provide the Paradyn Parallel Performance Tools (below
 * described as "Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 * 
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#if !defined(IA_X86_DETAILS_H)
#define IA_X86_DETAILS_H

#include "CFG.h"
#include "dyntypes.h"
#include "IA_platformDetails.h"

namespace Dyninst
{
    namespace InsnAdapter
    {
        
        class IA_x86Details : public IA_platformDetails
        {
            friend IA_platformDetails* makePlatformDetails(Dyninst::Architecture Arch, const IA_IAPI* cb);
            protected:
                IA_x86Details(const IA_IAPI* cb) :
                    IA_platformDetails(cb) {}
            public:
                virtual ~IA_x86Details() {}
                virtual bool parseJumpTable(Dyninst::ParseAPI::Block* currBlk,
                                            std::vector<std::pair< Address, Dyninst::ParseAPI::EdgeTypeEnum > >& outEdges);
            private:
                bool isMovAPSTable(std::vector<std::pair< Address, Dyninst::ParseAPI::EdgeTypeEnum > >& outEdges);
                std::pair<Address, Address> findThunkAndOffset(Dyninst::ParseAPI::Block * start);
                bool isTableInsn(Dyninst::InstructionAPI::Instruction::Ptr i);
                std::map<Address, Dyninst::InstructionAPI::Instruction::Ptr>::const_iterator findTableInsn();
                boost::tuple<Dyninst::InstructionAPI::Instruction::Ptr,
                Dyninst::InstructionAPI::Instruction::Ptr,
                bool> findMaxSwitchInsn(Dyninst::ParseAPI::Block *start);
                Address findThunkInBlock(Dyninst::ParseAPI::Block * curBlock, Address& thunkOffset);
                bool computeTableBounds(Dyninst::InstructionAPI::Instruction::Ptr maxSwitchInsn,
                                        Dyninst::InstructionAPI::Instruction::Ptr branchInsn,
                                        Dyninst::InstructionAPI::Instruction::Ptr tableInsn,
                                        bool foundJCCAlongTaken,
                                        unsigned& tableSize,
                                        unsigned& tableStride);
                bool fillTableEntries(Address thunkOffset,
                                      Address tableBase,
                                      unsigned tableSize,
                                      unsigned tableStride,
                                      int offsetMultiplier,
                                      std::vector<std::pair< Address, Dyninst::ParseAPI::EdgeTypeEnum> >& outEdges);
                Address getTableAddress(Dyninst::InstructionAPI::Instruction::Ptr tableInsn,
                                        Address tableInsnAddr,
                                        Address thunkOffset);

        };
    }
}

#endif //!defined(IA_X86_DETAILS_H)