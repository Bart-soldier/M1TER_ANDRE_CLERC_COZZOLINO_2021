#include "DemoTER/utils/Parser.hpp"
#include "DemoTER/config.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include "glm/geometric.hpp"

void split(std::vector<std::string> &list, std::string str, std::string delimiter) {	
	list.clear();

	int pos = 0;
	while((pos = str.find(delimiter)) != std::string::npos) {
		list.push_back(str.substr(0, pos));
		str.erase(0, pos + delimiter.length());
	}

	list.push_back(str);
}

glm::vec3 calcTangent(glm::vec3 &n, glm::vec3 &p1, glm::vec3 &p2, glm::vec3 &p3, glm::vec2 &uv1, glm::vec2 &uv2, glm::vec2 &uv3) {
	glm::vec3 edge1 = p2 - p1;
	glm::vec3 edge2 = p3 - p1;
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;

	float f = 1. / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	glm::vec3 tangent;

	tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

	return tangent;
	//return glm::normalize(tangent - glm::dot(tangent, n) * n);
}

std::unique_ptr<Parser::Result> Parser::loadObj(const char *path) {
	std::cout << "Chargement de " << path << std::endl;

	std::ifstream file(std::string(RESOURCES_DIRECTORY).append(path).c_str());

	std::vector<glm::vec3> tmpVertex;
	std::vector<glm::vec3> tmpNormal; bool haveNormal = true;
	std::vector<glm::vec2> tmpUV; bool haveUV = true;
	std::vector<std::vector<int>> tmpFaces;

	std::string line;
	while(std::getline(file, line)) {
		if(line.empty()) continue;

		std::vector<std::string> list;
		split(list, line, " ");

		if(list[0].compare("v") == 0) {
			if(list.size() < 4) continue;
			tmpVertex.push_back(glm::vec3(std::stof(list[1]), std::stof(list[2]), std::stof(list[3])));
		} else if(list[0].compare("vn") == 0) {
			if(list.size() < 4) continue;
			tmpNormal.push_back(glm::vec3(std::stof(list[1]), std::stof(list[2]), std::stof(list[3])));
		} else if(list[0].compare("vt") == 0) {
			if(list.size() < 3) continue;
			tmpUV.push_back(glm::vec2(std::stof(list[1]), std::stof(list[2])));
		} else if(list[0].compare("f") == 0) {
			if(list.size() < 4) continue;
			
			for(int i = 0; i < 3; ++i) {
				std::vector<std::string> subStrs;
				split(subStrs, list[i + 1], "/");
				if(subStrs.size() < 1) continue;

				if(subStrs.size() < 2 || subStrs[1].empty()) haveUV = false;
				if(subStrs.size() < 3 || subStrs[2].empty()) haveNormal = false;

				std::vector<int> ids {
					std::stoi(subStrs[0]) - 1,
					haveUV ? std::stoi(subStrs[1]) - 1 : -1,
					haveNormal ? std::stoi(subStrs[2]) - 1 : -1
				};

				tmpFaces.push_back(ids);
			}
		}
	}

	file.close();

	std::unique_ptr<Result> result = std::make_unique<Result>();

	for(std::vector<int> &face : tmpFaces) {
		result->vertex.push_back(tmpVertex[face[0]]);
		if(haveUV) result->uv.push_back(tmpUV[face[1]]);
		if(haveNormal) result->normal.push_back(tmpNormal[face[2]]);
	}

	if(haveNormal && haveUV) {
		for(int i = 0; i < result->vertex.size(); i += 3) {
			glm::vec3 &p1 = result->vertex[i];
			glm::vec3 &p2 = result->vertex[i+1];
			glm::vec3 &p3 = result->vertex[i+2];

			glm::vec3 &n1 = result->normal[i];
			glm::vec3 &n2 = result->normal[i + 1];
			glm::vec3 &n3 = result->normal[i + 2];

			glm::vec2 &uv1 = result->uv[i];
			glm::vec2 &uv2 = result->uv[i + 1];
			glm::vec2 &uv3 = result->uv[i + 2];

			result->tangent.push_back(calcTangent(n1, p1, p2, p3, uv1, uv2, uv3));
			result->tangent.push_back(calcTangent(n2, p2, p3, p1, uv2, uv3, uv1));
			result->tangent.push_back(calcTangent(n3, p3, p1, p2, uv3, uv1, uv2));
		}
	} else if(haveNormal) {
		for(glm::vec3 &n : result->normal) {
			result->tangent.push_back({n.y, -n.x, n.z});
		}
	}

	return result;
}
