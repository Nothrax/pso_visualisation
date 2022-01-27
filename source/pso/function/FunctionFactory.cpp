#include <pso/function/FunctionFactory.h>

#include <pso/function/Ackley.h>
#include <pso/function/CrossInTray.h>
#include <pso/function/Griewank.h>
#include <pso/function/Sphere.h>
#include <pso/function/SixHumpCamel.h>
#include <pso/function/Easom.h>
#include <pso/function/Michalewicz.h>
#include <pso/function/StyblinskiTang.h>
#include <pso/function/BukinN6.h>
#include <pso/function/DropWave.h>
#include <pso/function/HolderTable.h>
#include <pso/function/SchafferN4.h>
#include <pso/function/SchafferN2.h>
#include <pso/function/Levy.h>
#include <pso/function/LevyN13.h>

std::shared_ptr<Function> FunctionFactory::makeFunction(const std::string& functionName) {
    if(functionName == "Ackley"){
        return std::make_shared<Ackley>();
    }else if(functionName =="Cross-in-tray"){
        return std::make_shared<CrossInTray>();
    }else if(functionName =="Griewank"){
        return std::make_shared<Griewank>();
    }else if(functionName =="Sphere"){
        return std::make_shared<Sphere>();
    }else if(functionName =="Six-Hump Camel"){
        return std::make_shared<SixHumpCamel>();
    }else if(functionName =="Easom"){
        return std::make_shared<Easom>();
    }else if(functionName =="Michalewicz"){
        return std::make_shared<Michalewicz>();
    }else if(functionName =="Styblinski-Tang"){
        return std::make_shared<StyblinskiTang>();
    }else if(functionName =="Bukin N.6"){
        return std::make_shared<BukinN6>();
    }else if(functionName =="Drop-Wave"){
        return std::make_shared<DropWave>();
    }else if(functionName =="Holder Table"){
        return std::make_shared<HolderTable>();
    }else if(functionName =="Schaffer N.4"){
        return std::make_shared<SchafferN4>();
    }else if(functionName =="Schaffer N.2"){
        return std::make_shared<SchafferN2>();
    }else if(functionName =="Levy"){
        return std::make_shared<Levy>();
    }else if(functionName =="Levy N.13"){
        return std::make_shared<LevyN13>();
    }else{
        return nullptr;
    }
}

