/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/

#ifndef QMLJSMEMORYPOOL_P_H
#define QMLJSMEMORYPOOL_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qmljsglobal_p.h"

#include <qglobal.h>
#include <qshareddata.h>
#include <qdebug.h>

#include <cstring>

QT_QML_BEGIN_NAMESPACE

namespace QmlJS {

class QML_PARSER_EXPORT MemoryPool : public QSharedData
{
    MemoryPool(const MemoryPool &other);
    void operator =(const MemoryPool &other);

public:
    MemoryPool()
        : _blocks(0),
          _allocatedBlocks(0),
          _blockCount(-1),
          _ptr(0),
          _end(0)
    { }

    ~MemoryPool()
    {
        if (_blocks) {
            for (int i = 0; i < _allocatedBlocks; ++i) {
                if (char *b = _blocks[i])
                    qFree(b);
            }

            qFree(_blocks);
        }
    }

    inline void *allocate(size_t size)
    {
        size = (size + 7) & ~7;
        if (_ptr && (_ptr + size < _end)) {
            void *addr = _ptr;
            _ptr += size;
            return addr;
        }
        return allocate_helper(size);
    }

    void reset()
    {
        _blockCount = -1;
        _ptr = _end = 0;
    }

private:
    void *allocate_helper(size_t size)
    {
        Q_ASSERT(size < BLOCK_SIZE);

        if (++_blockCount == _allocatedBlocks) {
            if (! _allocatedBlocks)
                _allocatedBlocks = DEFAULT_BLOCK_COUNT;
            else
                _allocatedBlocks *= 2;

            _blocks = (char **) qRealloc(_blocks, sizeof(char *) * _allocatedBlocks);

            for (int index = _blockCount; index < _allocatedBlocks; ++index)
                _blocks[index] = 0;
        }

        char *&block = _blocks[_blockCount];

        if (! block)
            block = (char *) qMalloc(BLOCK_SIZE);

        _ptr = block;
        _end = _ptr + BLOCK_SIZE;

        void *addr = _ptr;
        _ptr += size;
        return addr;
    }

private:
    char **_blocks;
    int _allocatedBlocks;
    int _blockCount;
    char *_ptr;
    char *_end;

    enum
    {
        BLOCK_SIZE = 8 * 1024,
        DEFAULT_BLOCK_COUNT = 8
    };
};

class QML_PARSER_EXPORT Managed
{
    Managed(const Managed &other);
    void operator = (const Managed &other);

public:
    Managed() {}
    ~Managed() {}

    void *operator new(size_t size, MemoryPool *pool) { return pool->allocate(size); }
    void operator delete(void *) {}
    void operator delete(void *, MemoryPool *) {}
};

} // namespace QmlJS

QT_QML_END_NAMESPACE

#endif
