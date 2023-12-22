#in hindsight, it really did not have to be this complicated

import timeit

def solution(l):
	#create dictionary tree from input
	major_dict = {}
	for ver in l:
		version_as_list = [int(s) for s in ver.split(".")]
		#append placeholder -1's when version doesn't include all 3 numbers for sorting purposes
		version_as_list.extend([-1 for i in range(3 - len(version_as_list))])
		major_dict.setdefault(version_as_list[0], []).append(version_as_list)
	#keep sorted list of major version numbers
	major_versions = sorted(major_dict.keys())
	#keep list of sorted lists of minor version numbers
	minor_versions = []
	#create second level of tree
	for i in major_versions:
		minor_dict = {}
		for ver in major_dict[i]:
			minor_dict.setdefault(ver[1], []).append(ver)
			#can just sort leaves in place
			minor_dict[ver[1]].sort(key = lambda v: v[2])
		major_dict[i] = minor_dict
		minor_versions.append(sorted(major_dict[i].keys()))
	#flatten tree using major_versions and minor_versions
	final_sorted_list = []
	for i in range(len(major_versions)):
		for j in minor_versions[i]:
			final_sorted_list.extend(major_dict[major_versions[i]][j])
	#remove -1's and re-stringify
	return [".".join(str(i) for i in filter(lambda n: n != -1, ver)) for ver in final_sorted_list]
