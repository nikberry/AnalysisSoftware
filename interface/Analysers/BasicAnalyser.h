/*
 * BasicAnalyser.h
 *
 *  Created on: 3 Jul 2011
 *      Author: kreczko
 */

#ifndef BASICANALYSER_H_
#define BASICANALYSER_H_
#include <boost/shared_ptr.hpp>
#include "../../interface/TopPairEventCandidate.h"
#include "../../interface/HistHelpers/HistogramManager.h"

namespace BAT{
class BasicAnalyser{
protected:
    boost::shared_ptr<HistogramManager> histMan;

public:
    BasicAnalyser(boost::shared_ptr<HistogramManager> histMan);
    virtual ~BasicAnalyser();
    virtual void analyse(const TopPairEventCandidate& ttbarEvent) = 0;
    virtual void createHistograms() = 0;
};
}


#endif /* BASICANALYSER_H_ */