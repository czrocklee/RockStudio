// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_PROTOCOL_RS_ML_CORE_H_
#define FLATBUFFERS_GENERATED_PROTOCOL_RS_ML_CORE_H_

#include "flatbuffers/flatbuffers.h"

namespace rs {
namespace ml {
namespace core {

struct AudioSource;

struct Index;

struct Track;

MANUALLY_ALIGNED_STRUCT(2) Index FLATBUFFERS_FINAL_CLASS {
 private:
  uint16_t trackNumber_;
  uint16_t totalTracks_;
  uint16_t discNumber_;
  uint16_t totalDiscs_;

 public:
  Index() {
    memset(this, 0, sizeof(Index));
  }
  Index(const Index &_o) {
    memcpy(this, &_o, sizeof(Index));
  }
  Index(uint16_t _trackNumber, uint16_t _totalTracks, uint16_t _discNumber, uint16_t _totalDiscs)
      : trackNumber_(flatbuffers::EndianScalar(_trackNumber)),
        totalTracks_(flatbuffers::EndianScalar(_totalTracks)),
        discNumber_(flatbuffers::EndianScalar(_discNumber)),
        totalDiscs_(flatbuffers::EndianScalar(_totalDiscs)) {
  }
  uint16_t trackNumber() const {
    return flatbuffers::EndianScalar(trackNumber_);
  }
  uint16_t totalTracks() const {
    return flatbuffers::EndianScalar(totalTracks_);
  }
  uint16_t discNumber() const {
    return flatbuffers::EndianScalar(discNumber_);
  }
  uint16_t totalDiscs() const {
    return flatbuffers::EndianScalar(totalDiscs_);
  }
};
STRUCT_END(Index, 8);

struct AudioSource FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_FILEPATH = 4,
    VT_LASTMODIFIED = 6,
    VT_LENGTH = 8,
    VT_BITRATE = 10,
    VT_SAMPLERATE = 12,
    VT_BITDEPTH = 14
  };
  const flatbuffers::String *filepath() const {
    return GetPointer<const flatbuffers::String *>(VT_FILEPATH);
  }
  uint64_t lastModified() const {
    return GetField<uint64_t>(VT_LASTMODIFIED, 0);
  }
  uint32_t length() const {
    return GetField<uint32_t>(VT_LENGTH, 0);
  }
  uint32_t bitRate() const {
    return GetField<uint32_t>(VT_BITRATE, 0);
  }
  uint32_t sampleRate() const {
    return GetField<uint32_t>(VT_SAMPLERATE, 0);
  }
  uint8_t bitDepth() const {
    return GetField<uint8_t>(VT_BITDEPTH, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_FILEPATH) &&
           verifier.Verify(filepath()) &&
           VerifyField<uint64_t>(verifier, VT_LASTMODIFIED) &&
           VerifyField<uint32_t>(verifier, VT_LENGTH) &&
           VerifyField<uint32_t>(verifier, VT_BITRATE) &&
           VerifyField<uint32_t>(verifier, VT_SAMPLERATE) &&
           VerifyField<uint8_t>(verifier, VT_BITDEPTH) &&
           verifier.EndTable();
  }
};

struct AudioSourceBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_filepath(flatbuffers::Offset<flatbuffers::String> filepath) {
    fbb_.AddOffset(AudioSource::VT_FILEPATH, filepath);
  }
  void add_lastModified(uint64_t lastModified) {
    fbb_.AddElement<uint64_t>(AudioSource::VT_LASTMODIFIED, lastModified, 0);
  }
  void add_length(uint32_t length) {
    fbb_.AddElement<uint32_t>(AudioSource::VT_LENGTH, length, 0);
  }
  void add_bitRate(uint32_t bitRate) {
    fbb_.AddElement<uint32_t>(AudioSource::VT_BITRATE, bitRate, 0);
  }
  void add_sampleRate(uint32_t sampleRate) {
    fbb_.AddElement<uint32_t>(AudioSource::VT_SAMPLERATE, sampleRate, 0);
  }
  void add_bitDepth(uint8_t bitDepth) {
    fbb_.AddElement<uint8_t>(AudioSource::VT_BITDEPTH, bitDepth, 0);
  }
  AudioSourceBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  AudioSourceBuilder &operator=(const AudioSourceBuilder &);
  flatbuffers::Offset<AudioSource> Finish() {
    const auto end = fbb_.EndTable(start_, 6);
    auto o = flatbuffers::Offset<AudioSource>(end);
    return o;
  }
};

inline flatbuffers::Offset<AudioSource> CreateAudioSource(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> filepath = 0,
    uint64_t lastModified = 0,
    uint32_t length = 0,
    uint32_t bitRate = 0,
    uint32_t sampleRate = 0,
    uint8_t bitDepth = 0) {
  AudioSourceBuilder builder_(_fbb);
  builder_.add_lastModified(lastModified);
  builder_.add_sampleRate(sampleRate);
  builder_.add_bitRate(bitRate);
  builder_.add_length(length);
  builder_.add_filepath(filepath);
  builder_.add_bitDepth(bitDepth);
  return builder_.Finish();
}

inline flatbuffers::Offset<AudioSource> CreateAudioSourceDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *filepath = nullptr,
    uint64_t lastModified = 0,
    uint32_t length = 0,
    uint32_t bitRate = 0,
    uint32_t sampleRate = 0,
    uint8_t bitDepth = 0) {
  return rs::ml::core::CreateAudioSource(
      _fbb,
      filepath ? _fbb.CreateString(filepath) : 0,
      lastModified,
      length,
      bitRate,
      sampleRate,
      bitDepth);
}

struct Track FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_TITLE = 4,
    VT_ARTIST = 6,
    VT_ALBUM = 8,
    VT_ALBUMARTIST = 10,
    VT_GENRE = 12,
    VT_INDEX = 14,
    VT_SOURCE = 16
  };
  const flatbuffers::String *title() const {
    return GetPointer<const flatbuffers::String *>(VT_TITLE);
  }
  const flatbuffers::String *artist() const {
    return GetPointer<const flatbuffers::String *>(VT_ARTIST);
  }
  const flatbuffers::String *album() const {
    return GetPointer<const flatbuffers::String *>(VT_ALBUM);
  }
  const flatbuffers::String *albumArtist() const {
    return GetPointer<const flatbuffers::String *>(VT_ALBUMARTIST);
  }
  const flatbuffers::String *genre() const {
    return GetPointer<const flatbuffers::String *>(VT_GENRE);
  }
  const Index *index() const {
    return GetStruct<const Index *>(VT_INDEX);
  }
  const AudioSource *source() const {
    return GetPointer<const AudioSource *>(VT_SOURCE);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_TITLE) &&
           verifier.Verify(title()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_ARTIST) &&
           verifier.Verify(artist()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_ALBUM) &&
           verifier.Verify(album()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_ALBUMARTIST) &&
           verifier.Verify(albumArtist()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_GENRE) &&
           verifier.Verify(genre()) &&
           VerifyField<Index>(verifier, VT_INDEX) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_SOURCE) &&
           verifier.VerifyTable(source()) &&
           verifier.EndTable();
  }
};

struct TrackBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_title(flatbuffers::Offset<flatbuffers::String> title) {
    fbb_.AddOffset(Track::VT_TITLE, title);
  }
  void add_artist(flatbuffers::Offset<flatbuffers::String> artist) {
    fbb_.AddOffset(Track::VT_ARTIST, artist);
  }
  void add_album(flatbuffers::Offset<flatbuffers::String> album) {
    fbb_.AddOffset(Track::VT_ALBUM, album);
  }
  void add_albumArtist(flatbuffers::Offset<flatbuffers::String> albumArtist) {
    fbb_.AddOffset(Track::VT_ALBUMARTIST, albumArtist);
  }
  void add_genre(flatbuffers::Offset<flatbuffers::String> genre) {
    fbb_.AddOffset(Track::VT_GENRE, genre);
  }
  void add_index(const Index *index) {
    fbb_.AddStruct(Track::VT_INDEX, index);
  }
  void add_source(flatbuffers::Offset<AudioSource> source) {
    fbb_.AddOffset(Track::VT_SOURCE, source);
  }
  TrackBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  TrackBuilder &operator=(const TrackBuilder &);
  flatbuffers::Offset<Track> Finish() {
    const auto end = fbb_.EndTable(start_, 7);
    auto o = flatbuffers::Offset<Track>(end);
    return o;
  }
};

inline flatbuffers::Offset<Track> CreateTrack(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> title = 0,
    flatbuffers::Offset<flatbuffers::String> artist = 0,
    flatbuffers::Offset<flatbuffers::String> album = 0,
    flatbuffers::Offset<flatbuffers::String> albumArtist = 0,
    flatbuffers::Offset<flatbuffers::String> genre = 0,
    const Index *index = 0,
    flatbuffers::Offset<AudioSource> source = 0) {
  TrackBuilder builder_(_fbb);
  builder_.add_source(source);
  builder_.add_index(index);
  builder_.add_genre(genre);
  builder_.add_albumArtist(albumArtist);
  builder_.add_album(album);
  builder_.add_artist(artist);
  builder_.add_title(title);
  return builder_.Finish();
}

inline flatbuffers::Offset<Track> CreateTrackDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *title = nullptr,
    const char *artist = nullptr,
    const char *album = nullptr,
    const char *albumArtist = nullptr,
    const char *genre = nullptr,
    const Index *index = 0,
    flatbuffers::Offset<AudioSource> source = 0) {
  return rs::ml::core::CreateTrack(
      _fbb,
      title ? _fbb.CreateString(title) : 0,
      artist ? _fbb.CreateString(artist) : 0,
      album ? _fbb.CreateString(album) : 0,
      albumArtist ? _fbb.CreateString(albumArtist) : 0,
      genre ? _fbb.CreateString(genre) : 0,
      index,
      source);
}

inline const rs::ml::core::Track *GetTrack(const void *buf) {
  return flatbuffers::GetRoot<rs::ml::core::Track>(buf);
}

inline bool VerifyTrackBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<rs::ml::core::Track>(nullptr);
}

inline void FinishTrackBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<rs::ml::core::Track> root) {
  fbb.Finish(root);
}

}  // namespace core
}  // namespace ml
}  // namespace rs

#endif  // FLATBUFFERS_GENERATED_PROTOCOL_RS_ML_CORE_H_
