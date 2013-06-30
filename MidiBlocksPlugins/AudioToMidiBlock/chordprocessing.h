/*
    Copyright (C) 2013  Adam Nash

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

  */

#ifndef CHORDPROCESSING_H
#define CHORDPROCESSING_H

#include <CLAM/InPort.hxx>
#include <CLAM/OutPort.hxx>
#include "CLAM/Processing.hxx"
#include "CLAM/ChordSegmentator.hxx"
#include "CLAM/DiscontinuousSegmentation.hxx"

#include <QObject>
#include <QString>

using namespace CLAM;


class ChordProcessing : public QObject, public Processing
{
    Q_OBJECT
public:
    ChordProcessing(QObject* parent = 0, const Config& config = Config());
    const char* GetClassName() const { return "ChordProcessing"; }

    bool Do()
    {
        bool result = Do(m_chordSegmentation.GetData(), m_pitchProfile.GetData());
        m_chordSegmentation.Consume();
        m_pitchProfile.Consume();
        return result;
    }

    bool Do(const DiscontinuousSegmentation& seg, const std::vector<float> pitches);

signals:
    void chordChanged(QString);
    void apparentNotes(QByteArray);

public slots:
    void setThreshold(double threshold) {m_threshold = threshold;}

private:
    InPort<DiscontinuousSegmentation> m_chordSegmentation;
    InPort<std::vector<float> > m_pitchProfile;

    double m_threshold;
};

#endif // CHORDPROCESSING_H
