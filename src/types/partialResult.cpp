// A C++17 library for language servers.
// Copyright © 2019-2020 otreblan
//
// libclsp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libclsp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libclsp.  If not, see <http://www.gnu.org/licenses/>.

#include <libclsp/types/partialResult.hpp>

namespace clsp
{

using namespace std;

const String PartialResultParams::partialResultTokenKey = "partialResultToken";

PartialResultParams::
	PartialResultParams(optional<ProgressToken> partialResultToken):
		partialResultToken(partialResultToken)
{};

PartialResultParams::PartialResultParams(){};
PartialResultParams::~PartialResultParams(){};

void PartialResultParams::fillInitializer(ObjectInitializer& initializer)
{
	auto& setterMap = initializer.setterMap;

	// Value setters

	// partialResultToken?:
	setterMap.emplace(
		partialResultTokenKey,
		ValueSetter{
			// String
			[this](String str)
			{
				partialResultToken = str;
			},

			// Number
			[this](Number n)
			{
				partialResultToken = n;
			},

			// Boolean
			nullopt,

			// Null
			nullopt,

			// Array
			nullopt,

			// Object
			nullopt
		}
	);

	// This
	initializer.object = this;
}

void PartialResultParams::partialWrite(JsonWriter &writer)
{
	// partialResultToken?
	if(partialResultToken.has_value())
	{
		writer.Key(partialResultTokenKey);
		visit(overload(
			[&writer](String& str)
			{
				writer.String(str);
			},
			[&writer](Number n)
			{
				writer.Number(n);
			}
		), *partialResultToken);
	}
}

}
