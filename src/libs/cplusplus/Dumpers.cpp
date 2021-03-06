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

#include "Dumpers.h"

#include <Overview.h>
#include <Literals.h>
#include <Scope.h>
#include <LookupContext.h>
#include <QDebug>

#include <typeinfo>

static QString indent(QString s, int level = 2)
{
    QString indentString(level, QLatin1Char(' '));
    QString result;
    int last = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (s.at(i) == QLatin1Char('\n') || i == s.length() - 1) {
            result.append(indentString);
            result.append(s.midRef(last, i + 1));
            last = i + 1;
        }
    }
    return result;
}

QString CPlusPlus::toString(const Name *name, QString id)
{
    Overview oo;
    return QString("%0: %1").arg(id, name ? oo(name) : QLatin1String("(null)"));
}

QString CPlusPlus::toString(FullySpecifiedType ty, QString id)
{
    Overview oo;
    return QString("%0: %1 (a %2)").arg(id, oo(ty), ty.type() ? typeid(*ty.type()).name() : "(null)");
}

QString CPlusPlus::toString(const Symbol *s, QString id)
{
    if (!s)
        return QString("%0: (null)").arg(id);

    return QString("%0: %1 (%2) at %3:%4:%5\n%6").arg(
                id,
                QString::fromLatin1(typeid(*s).name()),
                QString::fromUtf8(s->identifier()->chars()),
                QString::fromLatin1(s->fileName()),
                QString::number(s->line()),
                QString::number(s->column()),
                indent(toString(s->type())));
}

QString CPlusPlus::toString(LookupItem it, QString id)
{
    QString result = QString("%1:").arg(id);
    if (it.declaration()) {
        result.append(QString("\n%1").arg(indent(toString(it.declaration(), QLatin1String("Decl")))));
    }
    if (it.type().isValid()) {
        result.append(QString("\n%1").arg(indent(toString(it.type()))));
    }
    if (it.scope()) {
        result.append(QString("\n%1").arg(indent(toString(it.scope(), QLatin1String("Scope")))));
    }
    if (it.binding()) {
        result.append(QString("\n%1").arg(indent(toString(it.binding(), QLatin1String("Binding")))));
    }
    return result;
}

QString CPlusPlus::toString(const ClassOrNamespace *binding, QString id)
{
    if (!binding)
        return QString("%0: (null)").arg(id);

    QString result = QString("%0: %1 symbols").arg(
                id,
                QString::number(binding->symbols().length()));
    if (binding->templateId()) {
        result.append(QString("\n%1").arg(indent(toString(binding->templateId(), QLatin1String("Template")))));
    }
    return result;
}

void CPlusPlus::dump(const Name *name)
{
    qDebug() << qPrintable(toString(name));
}

void CPlusPlus::dump(FullySpecifiedType ty)
{
    qDebug() << qPrintable(toString(ty));
}

void CPlusPlus::dump(const Symbol *s)
{
    qDebug() << qPrintable(toString(s));
}

void CPlusPlus::dump(LookupItem it)
{
    qDebug() << qPrintable(toString(it));
}

void CPlusPlus::dump(const ClassOrNamespace *binding)
{
    qDebug() << qPrintable(toString(binding));
}
