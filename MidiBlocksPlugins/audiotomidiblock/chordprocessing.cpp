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

#include "chordprocessing.h"
#include <QDebug>
#include <CLAM/ProcessingFactory.hxx>

ChordProcessing::ChordProcessing(QObject *parent, const Config &config) :
    QObject(parent),
    m_chordSegmentation("Chord Segmentation", this),
    m_pitchProfile("Pitch Profile", this)
{
    Configure( config );

    m_threshold = 0.009;
}

bool ChordProcessing::Do(const DiscontinuousSegmentation& in, const std::vector<float> pitches)
{
    if (in.onsets().size() > 0)
    {
        emit chordChanged(in.labels().back().c_str());
    }

    QByteArray notes;
    for (unsigned int i = 0; i<pitches.size(); i++)
    {
        if (pitches.at(i) > m_threshold)
        {
            notes += static_cast<char>((i+7)%12);
        }
    }
    if (!notes.isEmpty())
    {
        emit apparentNotes(notes);
    }

    return true;
}

static const char * metadata[] = {
    "key", "ChordProcessing",
    "category", "Analysis",
    0
};
static FactoryRegistrator<ProcessingFactory, ChordProcessing> registrator(metadata);
